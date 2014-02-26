#pragma once
#include "D3DDevice.h"
#include "TShader.h"

class TD3DDevice;
class TShader;

struct Vertex{
	FLOAT x,y,z;
};

class TBuffer
{
public:
	TBuffer(TD3DDevice* device, TShader * shader);
	~TBuffer();
	int CreateVertexBuffer();
	int CreateIndexBuffer();
	void PostRenderResource();

private:
	TD3DDevice* Device;
	TShader * Shader;
	ID3D11InputLayout* VertexLayout;
	ID3D11Buffer* VertexBuffer;
	ID3D11Buffer* IndexBuffer;
	UINT VertexBufferSize;
};

