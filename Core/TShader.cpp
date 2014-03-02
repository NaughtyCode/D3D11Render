#include "stdafx.h"
#include "TShader.h"
#include "TRender.h"

extern TRender* g_Render; 

TShader::TShader(TD3DDevice* device):Device(device),
				InputLayout(0),
				VertexShader(0),
				PixelShader(0),
				VertexShaderBuffer(0),
				PixelShaderBuffer(0),
				ConstantBufferData(0),
				LayoutType(LAYOUTTYPE_UNKNOWN)
{
	
}

TShader::~TShader()
{
	
}

int TShader::CompileShaderFromFile(const TCHAR* filename,
			LPCSTR entry,
			LPCSTR shadermodel,
			ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif
	ID3DBlob* pError;
	hr = D3DX11CompileFromFile(filename,
			NULL, NULL,
			entry,
			shadermodel,
			dwShaderFlags,
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

int TShader::CreateVertexShader(const TCHAR* filename,
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
	
	hr = Device->GetDevice()->CreateVertexShader(
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
	if (FAILED(Device->GetDevice()->CreateInputLayout(Desc,
		Num,
		this->GetShaderBufferPointer(),
		this->GetShaderBufferSize(),
		&InputLayout)))
	{
		return 0;
	}
	return 1;
}

int TShader::CreatePixelShader(const TCHAR* filename,
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
	
	hr = Device->GetDevice()->CreatePixelShader(
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
	this->UpdateConstantBuffer();
	return 1;
}

int TShader::CreateConstantBuffer()
{
	HRESULT hr;
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc,sizeof(D3D11_BUFFER_DESC));
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(TConstantBufferData);
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	hr = Device->GetDevice()->CreateBuffer(&BufferDesc,NULL,&ConstantBufferData);
	if( FAILED( hr ) )
	{
		return 0;
	}
	return 1;
}

void TShader::UpdateConstantBuffer()
{
	
}

void TShader::UpdateConstantBufferFrame()
{
	
}

void TShader::PostEffect()
{
	TCamera* camera;
	TConstantBufferData Data;
	ID3D11DeviceContext* DeviceContext;
	
	DeviceContext = Device->GetDeviceContext();
	camera = g_Render->GetCamera();
	
	Data.View = camera->GetTransposeView();
	Data.World = camera->RotationY(0.35f);
	Data.Projection = camera->GetTransposeProjection();
	
	DeviceContext->UpdateSubresource(ConstantBufferData,
					0,
					NULL,
					&Data,
					0,
					0);
	
	DeviceContext->IASetInputLayout(InputLayout);
	DeviceContext->VSSetConstantBuffers(0,1,&ConstantBufferData);
	DeviceContext->VSSetShader(VertexShader, NULL, 0);
	DeviceContext->PSSetShader(PixelShader, NULL, 0);
}

LPVOID TShader::GetShaderBufferPointer()
{
	assert(VertexShaderBuffer);
	return VertexShaderBuffer->GetBufferPointer();
}

SIZE_T TShader::GetShaderBufferSize()
{
	assert(VertexShaderBuffer);
	return VertexShaderBuffer->GetBufferSize();
}

void TShader::SetLayoutType(INPUTTYPE_TYPE type)
{
	LayoutType=type;
}

void TShader::Release()
{
	SAFE_RELEASE(VertexShader);
	SAFE_RELEASE(PixelShader);
	SAFE_RELEASE(VertexShaderBuffer);
	SAFE_RELEASE(PixelShaderBuffer);
	SAFE_RELEASE(ConstantBufferData);
	SAFE_RELEASE(InputLayout);
}









