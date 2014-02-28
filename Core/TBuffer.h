#pragma once
#include "TD3DDevice.h"
#include "TShader.h"
#include "TEffectShader.h"
#include "TInputLayout.h"
#include "IShader.h"

class IShader;
class TD3DDevice;
class TShader;
class TEffectShader;
class TInputLayout;

class TBuffer
{
public:
	TBuffer(TD3DDevice* device);
	~TBuffer();
	int CreateStaticVertexBuffer(UINT size,void* pData);
	int CreateVertexBuffer(void* pData,UINT size,UINT elemsize,bool dynamic,bool streamout);
	int CreateIndexBuffer(UINT size,bool dynamic,D3D11_SUBRESOURCE_DATA*pData);
	int CreateInputLayout(IShader * shader);
	void PostRenderResource();

private:
	TD3DDevice*        Device;
	TInputLayout*      InputLayout;  
	ID3D11Buffer*      VertexBuffer;
	ID3D11Buffer*      IndexBuffer;
	UINT               VertexBufferSize;
};

