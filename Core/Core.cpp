#include "stdafx.h"

#include "Core.h"


class TRender;
class TCamera;


TRender* GRender=NULL;

TCamera* GCamera=NULL;



void CreateRender(HWND hWnd)
{
	assert(!GRender);
	GRender = new TRender();
	GRender->CreateRender(hWnd);
	assert(!GCamera);
	GCamera = new TCamera(hWnd);
}



void DestroyRender()
{
	SAFE_DELETERELEASE(GCamera);
	SAFE_DELETERELEASE(GRender);
}

















