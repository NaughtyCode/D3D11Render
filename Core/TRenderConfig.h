#ifndef TRENDERCONFIG_H
#define TRENDERCONFIG_H

#if _MSC_VER > 1000
# pragma once
#endif

class TRenderConfig
{
public:
	TRenderConfig();
	~TRenderConfig();
	void SetHandle(UINT handle);
	void SetSize(UINT width,UINT height);
	UINT GetHandle();
	UINT GetWidth();
	UINT GetHeight();

private:
	UINT Handle;
	UINT Width;
	UINT Height;
};





#endif

