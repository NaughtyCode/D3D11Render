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
				ConstantBufferNeverChanges(0),
				ConstantBufferChangeOnResize(0),
				ConstantBufferChangesEveryFrame(0),
				Sampler(0),
				ObjectColor(0.7f,0.125f,0.8f,1.0f),
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
	InputLayout = new TInputLayout(Device);
	int r = InputLayout->CreateInputLayout(this,LayoutType);
	assert(r);
	return r;
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
	int r;
	r = this->CreateConstantBuffer();
	assert(r);
	this->UpdateConstantBuffer();
	r = this->CreateSampler();
	assert(r);
	return 1;
}

int TShader::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc,sizeof(D3D11_BUFFER_DESC));
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.ByteWidth = sizeof(CBNeverChanges);
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	
	HRESULT hr;
	hr = Device->GetDevice()->CreateBuffer( &BufferDesc,
		NULL,
		&ConstantBufferNeverChanges );
	
	if( FAILED( hr ) )
	{
		return 0;
	}

	BufferDesc.ByteWidth = sizeof(CBChangeOnResize);
	hr = Device->GetDevice()->CreateBuffer( &BufferDesc,
		NULL,
		&ConstantBufferChangeOnResize );
	
	if( FAILED( hr ) )
	{
		return 0;
	}

	BufferDesc.ByteWidth = sizeof(CBChangesEveryFrame);
	hr = Device->GetDevice()->CreateBuffer( &BufferDesc,
		NULL, 
		&ConstantBufferChangesEveryFrame );
	if( FAILED( hr ) )
	{
		return 0;
	}
	return 1;
}

int TShader::CreateSampler()
{
	D3D11_SAMPLER_DESC SampleDesc;
	ZeroMemory( &SampleDesc, sizeof(SampleDesc) );
	SampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SampleDesc.MinLOD = 0;
	SampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	if( FAILED( Device->GetDevice()->CreateSamplerState(&SampleDesc,&Sampler) ) )
	{
		return 0;
	}
	return 1;
}

void TShader::UpdateConstantBuffer()
{
	CBNeverChanges cbNeverChanges;
	TCamera* camera=g_Render->GetCamera();
	cbNeverChanges.View = camera->GetTransposeView();
	Device->GetImmediateContext()->UpdateSubresource( ConstantBufferNeverChanges,
					0,
					NULL,
					&cbNeverChanges,
					0,
					0);
	
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.Projection = camera->GetTransposeProjection();
	Device->GetImmediateContext()->UpdateSubresource( ConstantBufferChangeOnResize,
				0,
				NULL,
				&cbChangesOnResize,
				0,
				0);
	
}

void TShader::UpdateConstantBufferFrame()
{
	TCamera* camera=g_Render->GetCamera();
	XMMATRIX world = camera->RotationY(0.35f);
	
	CBChangesEveryFrame ChangesEveryFrame;
	ChangesEveryFrame.World = world;
	ChangesEveryFrame.ObjectColor = ObjectColor;
	Device->GetImmediateContext()->UpdateSubresource( ConstantBufferChangesEveryFrame,
					0,
					NULL,
					&ChangesEveryFrame,
					0,
					0);
	
	Device->GetImmediateContext()->VSSetConstantBuffers( 0, 1, &ConstantBufferNeverChanges );
	Device->GetImmediateContext()->VSSetConstantBuffers( 1, 1, &ConstantBufferChangeOnResize );
	Device->GetImmediateContext()->VSSetConstantBuffers( 2, 1, &ConstantBufferChangesEveryFrame );
	Device->GetImmediateContext()->PSSetConstantBuffers( 2, 1, &ConstantBufferChangesEveryFrame );
	Device->GetImmediateContext()->PSSetSamplers(0,1,&Sampler);
}

void TShader::PostEffect()
{
	InputLayout->PostInputLayout();
	this->UpdateConstantBufferFrame();
	Device->GetImmediateContext()->VSSetShader(VertexShader, NULL, 0);
	Device->GetImmediateContext()->PSSetShader(PixelShader, NULL, 0);
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
	SAFE_RELEASE(ConstantBufferNeverChanges);
	SAFE_RELEASE(ConstantBufferChangeOnResize);
	SAFE_RELEASE(ConstantBufferChangesEveryFrame);
	SAFE_RELEASE(Sampler);
	SAFE_DELETERELEASE(InputLayout);
}









