#include "stdafx.h"
#include "TEffectShader.h"

TEffectShader::TEffectShader(TD3DDevice* device):Device(device),
							Effect(0),
							Technique(0),
							EffectBuffer(0)
{

}

TEffectShader::~TEffectShader(void)
{
	
}


int TEffectShader::CompileShaderFromFile(const TCHAR* szFileName,
				LPCSTR szShaderModel,
				ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	ID3DBlob* pError;
	hr = D3DX11CompileFromFile(szFileName,
				NULL,
				NULL,
				NULL,
				szShaderModel,
				dwShaderFlags,
				0,
				NULL,
				ppBlobOut,
				&pError,
				NULL);
	if (FAILED(hr))
	{
		if (pError != NULL)
			OutputDebugStringA((char*)pError->GetBufferPointer());
		SAFE_RELEASE(pError);
		return 0;
	}
	SAFE_RELEASE(pError);
	return 1;
}

int TEffectShader::CreateEffectShader(const TCHAR* szFileName)
{
	if (!CompileShaderFromFile(szFileName,"fx_5_0", &EffectBuffer)){
		return 0;
	}
	HRESULT hr=D3DX11CreateEffectFromMemory(EffectBuffer->GetBufferPointer(),
					EffectBuffer->GetBufferSize(),
					0,
					Device->GetDevice(),
					&Effect);
	
	if (FAILED(hr)){
		return 0;
	}
	Technique=Effect->GetTechniqueByName("BasicEffect");
	return 1;
}

LPVOID TEffectShader::GetShaderBufferPointer()
{
	D3DX11_PASS_DESC desc;
	Technique->GetPassByIndex(0)->GetDesc(&desc);
	return desc.pIAInputSignature;
}

SIZE_T TEffectShader::GetShaderBufferSize()
{
	D3DX11_PASS_DESC desc;
	Technique->GetPassByIndex(0)->GetDesc(&desc);
	return desc.IAInputSignatureSize;
}

void TEffectShader::PostEffect()
{
	D3DX11_TECHNIQUE_DESC  desc;
	ID3DX11EffectPass*     pass;
	Technique->GetDesc(&desc);
	int num = desc.Passes;
	for(int i=0;i<num;i++)
	{
		pass=Technique->GetPassByIndex(i);
		pass->Apply(0,Device->GetDeviceContext());
	}
}

void TEffectShader::Release()
{
	SAFE_RELEASE(Technique);
	SAFE_RELEASE(EffectBuffer);
	SAFE_RELEASE(Effect);
}
