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

int TBuffer::CreateVertexBuffer(TShader * shader)
{
	InputLayout=new TInputLayout(Device);
	assert(InputLayout->CreateInputLayout(shader,LAYOUTTYPE_POSITION));

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	VertexBufferSize = GetVertexDataSize();

	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(Vertex)*VertexBufferSize;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA SubresourceData;
	ZeroMemory(&SubresourceData, sizeof(SubresourceData));
	SubresourceData.pSysMem = GetVertexData();

	if ( FAILED(Device->GetDevice()->CreateBuffer(&BufferDesc,&SubresourceData,&VertexBuffer) ) ){
		return 0;
	}
	return 1;
}

int TBuffer::CreateVertexBuffer(TEffectShader * effect)
{
	InputLayout=new TInputLayout(Device);
	assert(InputLayout->CreateInputLayout(effect,LAYOUTTYPE_POSITION));

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	VertexBufferSize = GetVertexDataSize();

	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(Vertex)*VertexBufferSize;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA SubresourceData;
	ZeroMemory(&SubresourceData, sizeof(SubresourceData));
	SubresourceData.pSysMem = GetVertexData();

	if ( FAILED(Device->GetDevice()->CreateBuffer(&BufferDesc,&SubresourceData,&VertexBuffer) ) ){
		return 0;
	}
	return 1;
}

int TBuffer::CreateIndexBuffer()
{
	return 1;
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
