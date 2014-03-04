#ifndef CORE_H
#define CORE_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TRender.h"
#include "TCamera.h"

extern TRender* GRender;
extern TCamera* GCamera;

void CreateRender(HWND hWnd);

void DestroyRender();


















#endif