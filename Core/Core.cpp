#include "stdafx.h"

#include "Core.h"


class TRender;
class TCamera;


TRender* GRender=NULL;

TCamera* GCamera=NULL;



void CreateRender(HWND hWnd)
{
	assert(!GCamera);
	GCamera = new TCamera(hWnd);
	assert(GCamera);

	assert(!GRender);
	GRender = new TRender();
	GRender->CreateRender(hWnd);
	assert(GRender);
}



void DestroyRender()
{
	SAFE_DELETERELEASE(GCamera);
	SAFE_DELETERELEASE(GRender);
}

















