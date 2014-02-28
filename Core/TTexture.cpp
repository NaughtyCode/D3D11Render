#include "stdafx.h"
#include "TTexture.h"
#include "TD3DDevice.h"

TTexture::TTexture(TD3DDevice* device):Device(device),TextureView(0)
{
}

TTexture::~TTexture(void)
{
}

int TTexture::CreateTexture(const TCHAR* TextureFileName)
{
	HRESULT hr;
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
	return 1;
}

void TTexture::PostTexture()
{
	Device->GetImmediateContext()->PSSetShaderResources( 0, 1, &TextureView);
}

void TTexture::Release()
{
	SAFE_RELEASE(TextureView);
}
