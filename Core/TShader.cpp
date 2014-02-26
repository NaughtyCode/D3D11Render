#include "stdafx.h"
#include "TShader.h"


TShader::TShader(TD3DDevice* device):Device(device),
									VertexShaderBuffer(0),
									PixelShaderBuffer(0)
{
	
}

TShader::~TShader()
{
}

int TShader::CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	ID3DBlob* pError;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,dwShaderFlags, 0, NULL, ppBlobOut, &pError, NULL);
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

int TShader::CreateShaders(const WCHAR* VSFilename, const WCHAR* PSFilename, const char* szVertexShaderEntryPoint, const char* szPixelShaderEntryPoint)
{
	if (!CompileShaderFromFile(VSFilename, szVertexShaderEntryPoint, "vs_5_0", &VertexShaderBuffer)){
		return 0;
	}

	if (!CompileShaderFromFile(PSFilename, szPixelShaderEntryPoint, "ps_5_0", &PixelShaderBuffer)){
		return 0;
	}
	HRESULT hr;

	hr = Device->GetDevice()->CreateVertexShader(
		VertexShaderBuffer->GetBufferPointer(),
		VertexShaderBuffer->GetBufferSize(),
		NULL,
		&VertexShader);
	if (FAILED(hr)){
		return 0;
	}

	hr = Device->GetDevice()->CreatePixelShader(
		PixelShaderBuffer->GetBufferPointer(),
		PixelShaderBuffer->GetBufferSize(),
		NULL,
		&PixelShader);
	if (FAILED(hr)){
		return 0;
	}

	return 1;
}

void TShader::PostShaders()
{
	Device->GetImmediateContext()->VSSetShader(VertexShader, NULL, 0);
	Device->GetImmediateContext()->PSSetShader(PixelShader, NULL, 0);
}

LPVOID TShader::GetVSBufferPointer()
{
	assert(VertexShaderBuffer);
	return VertexShaderBuffer->GetBufferPointer();
}

SIZE_T TShader::GetVSBufferSize()
{
	assert(VertexShaderBuffer);
	return VertexShaderBuffer->GetBufferSize();
}

void TShader::Release()
{

}
