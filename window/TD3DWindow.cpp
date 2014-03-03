#include "stdafx.h"
#include "TD3DWindow.h"

extern TRender* g_Render;

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
		g_Render->RenderFrame();
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

TD3DWindow::TD3DWindow():
			WindowHandle(0),
			Width(0),
			Height(0),
			D3D11Render(0),
			MouseObject(0)
{
	
}

TD3DWindow::~TD3DWindow()
{

}

int TD3DWindow::CreateD3DWindow(UINT x,UINT y,UINT width,UINT height)
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
	WndClass.lpszClassName	= L"GDKRender";
	WndClass.hIconSm		= LoadIcon( NULL, ( LPCTSTR )IDI_D3DSHADERDEMO );

	if (!RegisterClassEx(&WndClass))
	{
		return 0;
	}
	WindowHandle = CreateWindow(L"GDKRender", L"GDK Render", WS_OVERLAPPEDWINDOW,x,y,width,height,0,0,0,0);
	if (!WindowHandle)
	{
		return 0;
	}
	
	D3D11Render = new TRender();
	D3D11Render->CreateRender(WindowHandle);
	ShowWindow(WindowHandle,1);
	UpdateWindow(WindowHandle);
	
	MouseObject = new TMouseObject(WindowHandle);
	int r=MouseObject->CreateDirectInput();
	assert(r);
	
	return 1;
}

void TD3DWindow::SetWindowPos(INT X,INT Y)
{
	RECT rect;
	UINT width,height;
	GetWindowRect(WindowHandle, &rect);
	width  = rect.right  - rect.left;
	height = rect.bottom - rect.top;
	::SetWindowPos(WindowHandle,NULL,X,Y,width,height,SWP_SHOWWINDOW);
}

void TD3DWindow::SetWindowTitle(const TCHAR* Title)
{
	if (!WindowHandle)
	{
		::SetWindowText(WindowHandle,Title);
	}
}

void TD3DWindow::SetWindowSize(UINT width,UINT height)
{
	RECT rect;
	GetWindowRect(WindowHandle, &rect);
	::SetWindowPos(WindowHandle,NULL,rect.left,rect.top,width,height,SWP_NOMOVE);
}

void TD3DWindow::EnterLoop()
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
		else
		{
			D3D11Render->RenderFrame();
		}

		MouseObject->UpdateInputState();
	}
}

void TD3DWindow::Release()
{
	SAFE_DELETERELEASE(MouseObject);
	SAFE_DELETERELEASE(D3D11Render);
}

