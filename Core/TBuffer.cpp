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
								ElementSize(0),
								IndexDraw(FALSE)
{
}

TBuffer::~TBuffer()
{
}

int TBuffer::CreateStaticVertexBuffer(void* pData,UINT size,UINT elemsize)
{
	ElementSize = elemsize;
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	VertexBufferSize = size;

	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = ElementSize*VertexBufferSize;
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

int TBuffer::CreateVertexBuffer( void* pData,UINT size,UINT elemsize,bool dynamic,bool streamout)
{
	VertexBufferSize=size;
	ElementSize = elemsize;
	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.ByteWidth = size*elemsize;
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

int TBuffer::CreateIndexBuffer(void* pData,UINT size,bool dynamic)
{
	IndexBufferSize=size;
	IndexDraw=TRUE;
	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.ByteWidth = size;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;
	BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	if ( dynamic ){
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
	Device->GetImmediateContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &ElementSize, &offset);
	Device->GetImmediateContext()->IASetIndexBuffer( IndexBuffer, DXGI_FORMAT_R16_UINT, 0 );
	Device->GetImmediateContext()->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

	if (IndexDraw)
	{
		Device->GetImmediateContext()->DrawIndexed(IndexBufferSize, 0, 0 );
	}else
	{
		Device->GetImmediateContext()->Draw(VertexBufferSize,0);
	}
}

void TBuffer::Release()
{
	SAFE_RELEASE(VertexBuffer);
	SAFE_RELEASE(IndexBuffer);
	SAFE_RELEASE(InputLayout);
}
