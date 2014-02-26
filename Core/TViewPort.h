#pragma once
#include "TD3DDevice.h"

class TD3DDevice;

class TViewPort
{
public:
	TViewPort(TD3DDevice* device);
	~TViewPort();
	int CreateViewPort();
	void Release();

private:
	TD3DDevice* Device;
};

