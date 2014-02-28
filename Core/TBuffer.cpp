#include "stdafx.h"
#include "TBuffer.h"
#include "LayoutDefinitions.h"
#include "RenderData.h"

TBuffer::TBuffer(TD3DDevice* device) :
								Device(device),
								InputLayout(0),
								VertexBuffer(0),
								IndexBuffer(0)
{
}

TBuffer::~TBuffer()
{
}

int TBuffer::CreateStaticVertexBuffer(UINT size,void* pData)
{
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	VertexBufferSize = size;

	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(Vertex)*VertexBufferSize;
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

int TBuffer::CreateIndexBuffer(UINT size,bool dynamic,D3D11_SUBRESOURCE_DATA*pData)
{
	D3D11_BUFFER_DESC desc;
	desc.ByteWidth = size;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;
	desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	if ( dynamic ){
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}
	else{
		desc.Usage = D3D11_USAGE_IMMUTABLE;
		desc.CPUAccessFlags = 0;
	}
	if ( FAILED( Device->GetDevice()->CreateBuffer( &desc, pData, &IndexBuffer ) ) ){
		return 0;
	}
	return 1;
}

int TBuffer::CreateInputLayout(IShader * shader)
{
	InputLayout = new TInputLayout(Device);
	if ( InputLayout->CreateInputLayout(shader,LAYOUTTYPE_POSITION)){
		return 1;
	}
	return 0;
}

void TBuffer::PostRenderResource()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	InputLayout->PostInputLayout();
	Device->GetImmediateContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	Device->GetImmediateContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Device->GetImmediateContext()->Draw(VertexBufferSize,0);
}
