#include "stdafx.h"
#include "TBuffer.h"
#include "LayoutDefinitions.h"



TBuffer::TBuffer(TD3DDevice* device, TShader * shader) :
								Device(device),
								Shader(shader),
								VertexLayout(0),
								VertexBuffer(0),
								IndexBuffer(0)
{

}

TBuffer::~TBuffer()
{
}

int TBuffer::CreateVertexBuffer()
{
	D3D11_INPUT_ELEMENT_DESC* desc = GetInputElementDesc(LAYOUTTYPE_POSITION);
	UINT Num = (UINT)LAYOUTTYPE_POSITION+1U;
	if (FAILED(Device->GetDevice()->CreateInputLayout(desc,
		Num,
		Shader->GetVSBufferPointer(),
		Shader->GetVSBufferSize(),
		&VertexLayout)))
	{
		return 0;
	}

	Vertex Vertices[]=
	{
		0.0,-0.5,0.0,
		0.0,0.5,0.0,
		0.0,0.0,0.0,
		0.5,0.0,0.0,
		-0.5,0.0,0.0,
		0.0,0.0,0.0,
		0.1,0.1,0.0,
		0.0,0.0,0.0,
		0.5,0.0,0.0,
		0.5,0.1,0.0,
		0.5,0.0,0.0,
		0.0,0.0,0.0,
		-0.5,0.0,0.0,
		-0.5,0.1,0.0,
	};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	VertexBufferSize = ARRAYSIZE(Vertices);

	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(Vertex)*VertexBufferSize;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA SubresourceData;
	ZeroMemory(&SubresourceData, sizeof(SubresourceData));
	SubresourceData.pSysMem = Vertices;

	if ( FAILED(Device->GetDevice()->CreateBuffer(&BufferDesc,&SubresourceData,&VertexBuffer) ) ){
		return 0;
	}

	Device->GetImmediateContext()->IASetInputLayout(VertexLayout);
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	Device->GetImmediateContext()->IASetVertexBuffers(0, 1, &VertexBuffer, &stride, &offset);
	Device->GetImmediateContext()->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_LINESTRIP);
	return 1;
}

int TBuffer::CreateIndexBuffer()
{
	return 1;
}

void TBuffer::PostRenderResource()
{
	Device->GetImmediateContext()->Draw(VertexBufferSize,0);
}
