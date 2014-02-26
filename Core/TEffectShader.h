#pragma once
#include "TD3DDevice.h"

class TD3DDevice;

class TEffectShader
{
public:
	TEffectShader(TD3DDevice* device);
	virtual ~TEffectShader(void);
	int CompileShaderFromFile(const WCHAR* szFileName,LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	int CreateEffectShader(const WCHAR* szFileName);
	void PostEffectShader();
	LPVOID GetVSBufferPointer();
	SIZE_T GetVSBufferSize();

	void Release();
private:
	TD3DDevice*             Device;
	ID3DX11Effect*          Effect;
	ID3DX11EffectTechnique* Technique;
	ID3DBlob*               EffectBuffer;
};

