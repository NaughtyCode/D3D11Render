#pragma once

#include "resource.h"
#include "TRender.h"

class TRender;

class TD3DWindow
{
public:
	TD3DWindow();
	~TD3DWindow();
	int CreateD3DWindow();
	void Loop();
private:
	HWND hWnd;
	TRender* D3D11Render;
};
