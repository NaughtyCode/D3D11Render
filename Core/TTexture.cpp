#include "stdafx.h"
#include "TDevice.h"

TTexture::TTexture():TextureView(0)
{
	Device=GDevice->GetDevice();
	DeviceContext=GDevice->GetDeviceContext();
}

TTexture::~TTexture(void)
{
	
}

int TTexture::CreateTexture(const char* TextureFileName)
{
	HRESULT hr;
	hr=D3DX11CreateShaderResourceViewFromFileA( GDevice->GetDevice(),
		TextureFileName,
		NULL,
		NULL, 
		&TextureView, 
		NULL );
	if( FAILED(hr))
	{
		return 0;
	}
	this->CreateSampler();
	return 1;
}

int TTexture::CreateSampler()
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
	if( FAILED( Device->CreateSamplerState(&SampleDesc,&Sampler) ) )
	{
		return 0;
	}
	return 1;
}

void TTexture::PostTexture()
{
	DeviceContext->PSSetSamplers(0,1,&Sampler);
	DeviceContext->PSSetShaderResources(0,1,&TextureView);
}

void TTexture::Release()
{
	SAFE_RELEASE(TextureView);
	SAFE_RELEASE(Sampler);
}
