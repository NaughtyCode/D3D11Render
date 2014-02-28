#pragma once

#include "TD3DDevice.h"
#include "TRenderTarget.h"
#include "TViewPort.h"
#include "TResource.h"
#include "TRenderConfig.h"
#include "TCamera.h"


class TD3DDevice;
class TRenderTarget;
class TViewPort;
class TShader;
class TResource;
class TRenderConfig;
class TCamera;



class TRender
{
public:
	TRender();
	~TRender();
	int CreateRender(HWND hWnd);
	TCamera* GetCamera();
	void RenderFrame();

	void Release();
private:
	TD3DDevice*     Device;
	TRenderTarget*  RenderTarget;
	TViewPort*      ViewPort;
	TResource*      Resource;
	TCamera*        Camera;
};

extern TRender* g_Render;


