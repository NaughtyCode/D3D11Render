#include "stdafx.h"
#include "TRenderConfig.h"


TRenderConfig::TRenderConfig()
{
}

TRenderConfig::~TRenderConfig()
{
}

void TRenderConfig::SetHandle(UINT handle)
{
	Handle=handle;
}

void TRenderConfig::SetSize(UINT width,UINT height)
{
	Width=width;
	Height=height;
}

UINT TRenderConfig::GetHandle()
{
	return Handle;
}

UINT TRenderConfig::GetWidth()
{
	return Width;
}

UINT TRenderConfig::GetHeight()
{
	return Height;
}
