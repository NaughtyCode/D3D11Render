#include "stdafx.h"
#include "TBuffer.h"
#include "LayoutDefinitions.h"
#include "RenderData.h"

TBuffer::TBuffer(TD3DDevice* device) :
								Device(device),
								InputLayout(0),
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

int TBuffer::CreateInputLayout(IShader * shader,INPUTELEMENTDESCTYPE type)
{
	InputLayout = new TInputLayout(Device);
	if ( InputLayout->CreateInputLayout(shader,type)){
		return 1;
	}
	return 0;
}

void TBuffer::PostResource()
{
	UINT offset = 0;

	InputLayout->PostInputLayout();
	Device->GetImmediateContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &VertexSize, &offset);
	Device->GetImmediateContext()->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	Device->GetImmediateContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	if (IsIndexDraw){
		INT StartIndexLocation = 0;
		INT BaseVertexLocation = 0;
		Device->GetImmediateContext()->DrawIndexed(IndexBufferSize, StartIndexLocation, BaseVertexLocation );
	}else{
		INT StartVertexLocation = 0;
		Device->GetImmediateContext()->Draw(VertexBufferSize,StartVertexLocation);
	}
}

void TBuffer::Release()
{
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(IndexBuffer);
	SAFE_RELEASE(InputLayout);
}
