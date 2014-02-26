#include "stdafx.h"
#include "TBuffer.h"
#include "LayoutDefinitions.h"
#include "RenderData.h"

TBuffer::TBuffer(TD3DDevice* device) :
								Device(device),
								VertexLayout(0),
								VertexBuffer(0),
								IndexBuffer(0)
{
}

TBuffer::~TBuffer()
{
}

int TBuffer::CreateVertexBuffer(TShader * shader)
{
	D3D11_INPUT_ELEMENT_DESC* desc = GetInputElementDesc(LAYOUTTYPE_POSITION);
	UINT Num = (UINT)LAYOUTTYPE_POSITION+1U;
	if (FAILED(Device->GetDevice()->CreateInputLayout(desc,
		Num,
		shader->GetVSBufferPointer(),
		shader->GetVSBufferSize(),
		&VertexLayout)))
	{
		return 0;
	}

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
	D3D11_INPUT_ELEMENT_DESC* desc = GetInputElementDesc(LAYOUTTYPE_POSITION);
	UINT Num = (UINT)LAYOUTTYPE_POSITION+1U;
	if (FAILED(Device->GetDevice()->CreateInputLayout(desc,
		Num,
		effect->GetVSBufferPointer(),
		effect->GetVSBufferSize(),
		&VertexLayout)))
	{
		return 0;
	}

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
	Device->GetImmediateContext()->IASetInputLayout(VertexLayout);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Device->GetImmediateContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	Device->GetImmediateContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Device->GetImmediateContext()->Draw(VertexBufferSize,0);
}
