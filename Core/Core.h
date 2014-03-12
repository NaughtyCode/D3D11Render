#ifndef CORE_H
#define CORE_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TRender.h"
#include "TCamera.h"



























extern TRender*        GRender;
extern TCamera*        GCamera;
extern TD3DDevice*     GDevice;
extern DWORD           GGPUFrameTime;
extern char*           ResourceRoot;

void CreateRender(HWND hWnd);
void DestroyRender();

void GetResourceDirASCII(std::string& FileName);
void GetResourceDirWCHAR(std::wstring& FileName);












#endif