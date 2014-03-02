#ifndef TTEXTURE_H
#define TTEXTURE_H

#if _MSC_VER > 1000
# pragma once
#endif

class TD3DDevice;

class TTexture
{
public:
	TTexture(TD3DDevice* device);
	virtual ~TTexture(void);
	int CreateTexture(const TCHAR* TextureFileName);
	void PostTexture();
	void Release();

private:
	TD3DDevice*               Device;
	ID3D11ShaderResourceView* TextureView;
};


#endif
