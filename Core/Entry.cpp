#include "stdafx.h"
#include "TWindow.h"

class TWindow;

extern void LoadRenderConfig();



int main()
{
	
	
	LoadRenderConfig();
	
	TWindow Window;
	
	if(Window.CreateD3DWindow(0,0,1440,900))
	{
		Window.EnterLoop();
	}
	
	
	
	
	
	
	
	return 0;
}
