#ifndef D3DDEVICE_H
#define D3DDEVICE_H

#include"stdafx.h"


class TD3DDevice
{
public:
	TD3DDevice(HWND hWnd);
	virtual ~TD3DDevice();
	int CreateDevice();
	ID3D11Device* GetDevice();
	IDXGISwapChain* GetSwapChain();
	ID3D11DeviceContext* GetImmediateContext();
	HWND GetWindowHandle();
	void Release();

private:
	HWND Handle;
	ID3D11Device* Device;
	IDXGISwapChain* SwapChain;
	ID3D11DeviceContext* ImmediateContext;
};






#endif
