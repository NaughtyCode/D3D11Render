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
	int CreateStaticVertexBuffer(void* pData,UINT size,UINT elemsize);
	int CreateVertexBuffer(void* pData,UINT size,UINT elemsize,bool dynamic,bool streamout);
	int CreateIndexBuffer(void* pData,UINT size,bool dynamic);
	int CreateInputLayout(IShader * shader,INPUTELEMENTDESCTYPE type);
	void PostResource();
	void Release();

private:
	TD3DDevice*        Device;
	TInputLayout*      InputLayout;  
	ID3D11Buffer*      VertexBuffer;
	ID3D11Buffer*      IndexBuffer;
	UINT               VertexBufferSize;
	UINT               IndexBufferSize;
	UINT               ElementSize;
	BOOL               IndexDraw;
};

