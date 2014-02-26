#pragma once

#include "TD3DDevice.h"

class TD3DDevice;

class TRenderTarget
{
public:
	TRenderTarget(TD3DDevice* device);
	virtual ~TRenderTarget();
	int CreateRenderTarget();
	void Clear();
	ID3D11RenderTargetView* GetRenderTargetView();
	void Release();
private:
	TD3DDevice* Device;
	ID3D11RenderTargetView* RenderTargetView;
};

