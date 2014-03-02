#include "stdafx.h"
#include "TBuffer.h"
#include "RenderData.h"

TBuffer::TBuffer(TD3DDevice* device) :
			Device(device),
			VertexBuffer(0),
			IndexBuffer(0),
			VertexBufferSize(0),
			VertexSize(0),
			IsIndexDraw(FALSE)
{
	
}

TBuffer::~TBuffer()
{
	
}

int TBuffer::CreateStaticVertexBuffer(void* pData,UINT size,UINT elemsize)
{
	VertexSize = elemsize;
	VertexBufferSize = size;

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = VertexSize*VertexBufferSize;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA Data;
	ZeroMemory(&Data, sizeof(Data));
	Data.pSysMem = pData;

	if ( FAILED(Device->GetDevice()->CreateBuffer(&BufferDesc,&Data,&VertexBuffer) ) ){
		return 0;
	}
	return 1;
}

int TBuffer::CreateVertexBuffer( void* pData,UINT size,UINT vertexsize,bool dynamic,bool streamout)
{
	VertexBufferSize=size;
	this->VertexSize = vertexsize;
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory( &BufferDesc, sizeof(BufferDesc) );
	BufferDesc.ByteWidth = size*VertexSize;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;
	if (streamout){
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;
	}
	else{
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	}
	if (dynamic){
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else{
		BufferDesc.Usage = D3D11_USAGE_IMMUTABLE;
		BufferDesc.CPUAccessFlags = 0;
	}

	D3D11_SUBRESOURCE_DATA Data;
	ZeroMemory(&Data, sizeof(Data));
	Data.pSysMem = pData;

	if ( FAILED( Device->GetDevice()->CreateBuffer( &BufferDesc,&Data, &VertexBuffer ) ) ) {
		return 0;
	}
	return 1;
}

int TBuffer::CreateIndexBuffer(void* pData,UINT size,UINT indexsize,bool dynamic)
{
	IndexBufferSize=size;
	IsIndexDraw=TRUE;
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory( &BufferDesc,sizeof(BufferDesc));
	BufferDesc.ByteWidth = indexsize*size;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	if ( dynamic ){
		BufferDesc.Usage = D3D11_USAGE_DYNAMIC;
		BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else{
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.CPUAccessFlags = 0;
	}

	D3D11_SUBRESOURCE_DATA Data;
	ZeroMemory(&Data, sizeof(Data));
	Data.pSysMem = pData;

	if ( FAILED( Device->GetDevice()->CreateBuffer( &BufferDesc,&Data, &IndexBuffer ) ) ){
		return 0;
	}
	return 1;
}

void TBuffer::PostResource()
{
	UINT offset = 0;
	Device->GetDeviceContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexSize, &offset);
	Device->GetDeviceContext()->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	Device->GetDeviceContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );
	
	if (IsIndexDraw){
		INT StartIndexLocation = 0;
		INT BaseVertexLocation = 0;
		Device->GetDeviceContext()->DrawIndexed(IndexBufferSize, StartIndexLocation, BaseVertexLocation );
	}else{
		INT StartVertexLocation = 0;
		Device->GetDeviceContext()->Draw(VertexBufferSize,StartVertexLocation);
	}
}

void TBuffer::Release()
{
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(IndexBuffer);
}


//--------------------------------------ConstantBuffer-------------------------------------

TConstantBuffer::TConstantBuffer(TD3DDevice* device,WORD Size):
			Data(0),
			Device(device),
			NeedPost(FALSE),
			CurrentSize(0),
			BufferSize(Size),
			ConstantBuffer(0)
{
	
}

TConstantBuffer::~TConstantBuffer()
{
	
}

int TConstantBuffer::CreateConstantBuffer()
{
	// check constant buffer Width
	assert(BufferSize <= D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT && (BufferSize%16) == 0);
	
	HRESULT hr;
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc,sizeof(BufferDesc));
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = BufferSize;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	
	hr = Device->GetDevice()->CreateBuffer(
		&BufferDesc,
		NULL,
		&ConstantBuffer);
	
	if( FAILED( hr ) )
	{
		return 0;
	}
	
	Data = new BYTE[BufferSize];
	ZeroMemory(Data,BufferSize);
	return 1;
}

void TConstantBuffer::UpdateBuffer(const BYTE* Data, WORD Offset, WORD Size)
{
	NeedPost=TRUE;
	CopyMemory((void*)(Data+Offset),Data,Size);
	CurrentSize = max( (UINT)(Offset+Size),CurrentSize );
}

BOOL TConstantBuffer::PostConstantBuffer(BOOL IsDiscard)
{
	if(NeedPost)
	{
		if(CurrentSize>0)
		{
			Device->GetDeviceContext()->UpdateSubresource(ConstantBuffer,0,NULL,(void*)Data,CurrentSize,CurrentSize);
		}
		
		if(IsDiscard)
		{
			NeedPost = FALSE;
			CurrentSize = 0;
		}
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

ID3D11Buffer* TConstantBuffer::GetConstantBuffer()
{
	return ConstantBuffer;
}

void TConstantBuffer::Release()
{
	SAFE_DELETE_ARRAY(Data);
	SAFE_RELEASE(ConstantBuffer);
}
