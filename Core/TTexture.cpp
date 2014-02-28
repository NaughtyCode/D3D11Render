#include "stdafx.h"
#include "TTexture.h"
#include "TD3DDevice.h"

TTexture::TTexture(TD3DDevice* device):Device(device),TextureView(0),NumQuality(0)
{
}

TTexture::~TTexture(void)
{
}

int TTexture::CreateTexture(const TCHAR* TextureFileName)
{
	HRESULT hr;
	hr=Device->GetDevice()->CheckMultisampleQualityLevels(DXGI_FORMAT_R8G8B8A8_UNORM,
		4,
		&NumQuality );

	if (FAILED(hr))
	{
		return 0;
	}
	hr=D3DX11CreateShaderResourceViewFromFile( Device->GetDevice(),
		TextureFileName,
		NULL,
		NULL, 
		&TextureView, 
		NULL );

	if( FAILED(hr))
	{
		return 0;
	}

	D3D11_SAMPLER_DESC SampleDesc;
	ZeroMemory( &SampleDesc, sizeof(SampleDesc) );
	SampleDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SampleDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SampleDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	SampleDesc.MinLOD = 0;
	SampleDesc.MaxLOD = D3D11_FLOAT32_MAX;
	hr = Device->GetDevice()->CreateSamplerState( &SampleDesc, &SamplerLinear );
	if( FAILED( hr ) )
	{
		return 0;
	}
	
	return 1;
}

void TTexture::PostTexture()
{
	Device->GetImmediateContext()->PSSetShaderResources( 0, 1, &TextureView);
	Device->GetImmediateContext()->PSSetSamplers( 0, 1, &SamplerLinear);
}

void TTexture::Release()
{
	SAFE_RELEASE(SamplerLinear);
	SAFE_RELEASE(TextureView);
}
