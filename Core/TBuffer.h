#pragma once
#include "TD3DDevice.h"
#include "TShader.h"
#include "TEffectShader.h"
#include "TInputLayout.h"



class TD3DDevice;
class TShader;
class TEffectShader;
class TInputLayout;



class TBuffer
{
public:
	TBuffer(TD3DDevice* device);
	~TBuffer();
	int CreateVertexBuffer(TShader * shader);
	int CreateVertexBuffer(TEffectShader * effect);
	int CreateIndexBuffer();
	void PostRenderResource();

private:
	TD3DDevice*        Device;
	TInputLayout*      InputLayout;  
	ID3D11Buffer*      VertexBuffer;
	ID3D11Buffer*      IndexBuffer;
	UINT               VertexBufferSize;
};

