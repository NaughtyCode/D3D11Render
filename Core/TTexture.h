#pragma once

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
	ID3D11SamplerState*       SamplerLinear;
	UINT                      NumQuality;
};

