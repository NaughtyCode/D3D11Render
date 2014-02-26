#pragma once

#include "resource.h"
#include "TRender.h"

class TRender;

class D3DRenderWindow
{
public:
	D3DRenderWindow();
	~D3DRenderWindow();
	int CreateRenderWindow();
	void Loop();
private:
	HWND hWnd;
	TRender* D3D11Render;
};
