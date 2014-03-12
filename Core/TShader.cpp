#include "stdafx.h"
#include "Core.h"
#include "TRender.h"

TShader::TShader():
		HullShader(0),
		DomainShader(0),
		GeometryShader(0),
		InputLayout(0),
		VertexShader(0),
		PixelShader(0),
		VertexShaderBuffer(0),
		PixelShaderBuffer(0),
		ShaderResource(0),
		LayoutType(LAYOUTTYPE_UNKNOWN)
{

	DeviceContext=GDevice->GetDeviceContext();

}

TShader::~TShader()
{
	
}

int TShader::CompileShaderFromFile(const char* filename,
			LPCSTR entry,
			LPCSTR shadermodel,
			ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;
	DWORD CompileFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	CompileFlags |= D3DCOMPILE_DEBUG;
#endif
	ID3DBlob* pError;
	hr = D3DX11CompileFromFileA(filename,
			NULL, NULL,
			entry,
			shadermodel,
			CompileFlags,
			0,
			NULL,
			ppBlobOut,
			&pError,
			NULL);
	
	if (FAILED(hr))
	{
		if (pError != NULL)
		{
			OutputDebugStringA((char*)pError->GetBufferPointer());
		}
		SAFE_RELEASE(pError);
		return 0;
	}
	SAFE_RELEASE(pError);
	return 1;
}

int TShader::CreateVertexShader(const char* filename,
			const char* entry,
			const char* shadermodel)
{
	HRESULT hr;
	
	if (!CompileShaderFromFile(filename,
			entry,
			shadermodel,
			&VertexShaderBuffer))
	{
		return 0;
	}
	
	hr = GDevice->GetDevice()->CreateVertexShader(
		VertexShaderBuffer->GetBufferPointer(),
		VertexShaderBuffer->GetBufferSize(),
		NULL,
		&VertexShader);
	if (FAILED(hr))
	{
		return 0;
	}
	if(!CreateInputLayout())
	{
		return 0;
	}
	return 1;
}

int TShader::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC* Desc = GetLayoutArray(LayoutType);
	UINT Num = GetLayoutArraySize(LayoutType);
	if (FAILED(GDevice->GetDevice()->CreateInputLayout(Desc,
		Num,
		VertexShaderBuffer->GetBufferPointer(),
		VertexShaderBuffer->GetBufferSize(),
		&InputLayout)))
	{
		return 0;
	}
	return 1;
}

int TShader::CreatePixelShader(const char* filename,
			const char* entry,
			const char* shadermodel)
{
	HRESULT hr;
	if (!CompileShaderFromFile(filename,
			entry,
			shadermodel,
			&PixelShaderBuffer))
	{
		return 0;
	}
	
	hr = GDevice->GetDevice()->CreatePixelShader(
		PixelShaderBuffer->GetBufferPointer(),
		PixelShaderBuffer->GetBufferSize(),
		NULL,
		&PixelShader);
	if (FAILED(hr))
	{
		return 0;
	}
	
	return 1;
}

int TShader::InitConstantBuffer()
{
	this->CreateConstantBuffer();
	return 1;
}

int TShader::CreateConstantBuffer()
{
	ShaderResource = new TConstantBuffer(sizeof(TConstantBufferContents));
	ShaderResource->CreateConstantBuffer();
	return 1;
}

void TShader::PostEffect()
{
	struct TConstantBufferContents Data;
	
	Data.WorldViewProjectMatrix = GCamera->GetWorldViewProMatrix();
	
	ShaderResource->UpdateBufferData(&Data,0,sizeof(Data));
	ShaderResource->UpdateConstantBufferResource(TRUE);
	ShaderResource->PostConstantBuffer(0,1);
	
	DeviceContext->IASetInputLayout(InputLayout);
	DeviceContext->VSSetShader(VertexShader, NULL, 0);
	DeviceContext->PSSetShader(PixelShader, NULL, 0);
}

void TShader::SetLayoutType(INPUTTYPE_TYPE type)
{
	LayoutType=type;
}

void TShader::Release()
{
	SAFE_RELEASE(HullShader);
	SAFE_RELEASE(DomainShader);
	SAFE_RELEASE(GeometryShader);
	SAFE_RELEASE(VertexShader);
	SAFE_RELEASE(PixelShader);
	SAFE_RELEASE(VertexShaderBuffer);
	SAFE_RELEASE(PixelShaderBuffer);
	SAFE_RELEASEDELETE(ShaderResource);
	SAFE_RELEASE(InputLayout);
}









