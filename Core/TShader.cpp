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
				ObjectColor(1.0f,1.0f,1.0f,1.0f),
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

void TShader::UpdateConstantBuffer()
{
	CBNeverChanges cbNeverChanges;
	TCamera* camera=g_Render->GetCamera();
	cbNeverChanges.View = camera->GetTransposeView();
	Device->GetDeviceContext()->UpdateSubresource( ConstantBufferNeverChanges,
					0,
					NULL,
					&cbNeverChanges,
					0,
					0);
	
	CBChangeOnResize cbChangesOnResize;
	cbChangesOnResize.Projection = camera->GetTransposeProjection();
	Device->GetDeviceContext()->UpdateSubresource( ConstantBufferChangeOnResize,
				0,
				NULL,
				&cbChangesOnResize,
				0,
				0);
	
}

void TShader::UpdateConstantBufferFrame()
{
	
}

void TShader::PostEffect()
{
	Device->GetDeviceContext()->IASetInputLayout(InputLayout);
	TCamera* camera=g_Render->GetCamera();
	XMMATRIX world = camera->RotationY(0.35f);
	
	CBChangesEveryFrame ChangesEveryFrame;
	ChangesEveryFrame.World = world;
	ChangesEveryFrame.ObjectColor = ObjectColor;
	ID3D11DeviceContext* DeviceContext = Device->GetDeviceContext();
	
	DeviceContext->UpdateSubresource( ConstantBufferChangesEveryFrame,
					0,
					NULL,
					&ChangesEveryFrame,
					0,
					0);
	
	DeviceContext->VSSetConstantBuffers( 0, 1, &ConstantBufferNeverChanges );
	DeviceContext->VSSetConstantBuffers( 1, 1, &ConstantBufferChangeOnResize );
	DeviceContext->VSSetConstantBuffers( 2, 1, &ConstantBufferChangesEveryFrame );
	DeviceContext->PSSetConstantBuffers( 2, 1, &ConstantBufferChangesEveryFrame );
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
	SAFE_RELEASE(ConstantBufferNeverChanges);
	SAFE_RELEASE(ConstantBufferChangeOnResize);
	SAFE_RELEASE(ConstantBufferChangesEveryFrame);
	SAFE_RELEASE(InputLayout);
}









