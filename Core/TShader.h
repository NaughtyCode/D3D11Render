#pragma once
#include "TD3DDevice.h"

class TD3DDevice;

class TShader
{
public:
	TShader(TD3DDevice* device);
	~TShader();
	int CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	int CreateShaders(const WCHAR* VSFilename, const WCHAR* PSFilename, const char* vs, const char* ps);
	void PostShaders();
	LPVOID GetVSBufferPointer();
	SIZE_T GetVSBufferSize();

	void Release();
private:
	ID3DX11Effect*          Effect;
	ID3DX11EffectTechnique* Tech;
	TD3DDevice*             Device;
	ID3D11VertexShader*     VertexShader;
	ID3D11PixelShader*      PixelShader;
	ID3DBlob*               VertexShaderBuffer;
	ID3DBlob*               PixelShaderBuffer;
	ID3DBlob*               EffectBuffer;
};

