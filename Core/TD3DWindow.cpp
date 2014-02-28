#include "stdafx.h"
#include "TD3DWindow.h"

LRESULT CALLBACK RenderWindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

TD3DWindow::TD3DWindow():D3D11Render(0)
{

}

TD3DWindow::~TD3DWindow()
{

}

int TD3DWindow::CreateD3DWindow()
{
	WNDCLASSEX WndClass;

	WndClass.cbSize = sizeof(WNDCLASSEX);
	WndClass.style			= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc	= RenderWindowProc;
	WndClass.cbClsExtra		= 0;
	WndClass.cbWndExtra		= 0;
	WndClass.hInstance		= NULL;
	WndClass.hIcon			= LoadIcon( NULL, ( LPCTSTR )IDI_D3DSHADERDEMO );
	WndClass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	WndClass.lpszMenuName	= MAKEINTRESOURCE(IDC_D3DSHADERDEMO);
	WndClass.lpszClassName	= L"D3DRenderWindow";
	WndClass.hIconSm		= LoadIcon( NULL, ( LPCTSTR )IDI_D3DSHADERDEMO );

	if (!RegisterClassEx(&WndClass)){
		return 0;
	}
	hWnd = CreateWindow(L"D3DRenderWindow", L"D3DRender", WS_OVERLAPPEDWINDOW,100,80,1440,900,0,0,0,0);
	if (!hWnd){
		return 0;
	}

	D3D11Render = new TRender();
	D3D11Render->CreateRender(hWnd);
	ShowWindow(hWnd, 1);
	UpdateWindow(hWnd);

	return 1;
}

void TD3DWindow::Loop()
{
	MSG msg;
	HACCEL hAccelTable;
	hAccelTable = LoadAccelerators(NULL, MAKEINTRESOURCE(IDC_D3DSHADERDEMO));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		D3D11Render->RenderFrame();
	}
}
