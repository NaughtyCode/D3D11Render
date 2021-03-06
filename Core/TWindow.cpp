#include "stdafx.h"
#include "Core.h"
#include "TWindow.h"


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
		GDrawFrame();
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



TWindow::TWindow():
	WindowHandle(0),
	Width(0),
	Height(0),
	MouseObject(0)
{
	
}

TWindow::~TWindow()
{

}

int TWindow::CreateD3DWindow(UINT x,UINT y,UINT width,UINT height)
{
	WNDCLASSEX WndClass;

	WndClass.cbSize         = sizeof(WNDCLASSEX);
	WndClass.style		= CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc	= RenderWindowProc;
	WndClass.cbClsExtra	= 0;
	WndClass.cbWndExtra	= 0;
	WndClass.hInstance	= NULL;
	WndClass.hIcon		= LoadIcon( NULL, ( LPCTSTR )IDI_D3DSHADERDEMO );
	WndClass.hCursor	= LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	WndClass.lpszMenuName	= NULL;
	WndClass.lpszClassName	= L"GDKRender";
	WndClass.hIconSm	= LoadIcon( NULL, ( LPCTSTR )IDI_D3DSHADERDEMO );
	
	if (!RegisterClassEx(&WndClass))
	{
		return 0;
	}
	
	WindowHandle = CreateWindow(L"GDKRender", L"GDK", WS_OVERLAPPEDWINDOW,x,y,width,height,0,0,0,0);
	if (!WindowHandle)
	{
		return 0;
	}
	
	this->SetWindowPos(160,80);
	
	CreateRender(WindowHandle);
	
	ShowWindow(WindowHandle,1);
	UpdateWindow(WindowHandle);
	
	MouseObject = new TMouseObject(WindowHandle);
	int r=MouseObject->CreateDirectInput();
	assert(r);
	
	return 1;
}

void TWindow::SetWindowPos(INT X,INT Y)
{
	RECT rect;
	UINT width,height;
	GetWindowRect(WindowHandle, &rect);
	width  = rect.right  - rect.left;
	height = rect.bottom - rect.top;
	::SetWindowPos(WindowHandle,NULL,X,Y,width,height,SWP_SHOWWINDOW);
}

void TWindow::SetWindowTitle(const TCHAR* Title)
{
	if (!WindowHandle)
	{
		::SetWindowText(WindowHandle,Title);
	}
}

void TWindow::SetWindowSize(UINT width,UINT height)
{
	RECT rect;
	GetWindowRect(WindowHandle, &rect);
	::SetWindowPos(WindowHandle,NULL,rect.left,rect.top,width,height,SWP_NOMOVE);
}

void TWindow::EnterLoop()
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
		GDrawFrame();
		MouseObject->UpdateInputState();
	}
}

void TWindow::Release()
{
	SAFE_RELEASEDELETE(MouseObject);
}

