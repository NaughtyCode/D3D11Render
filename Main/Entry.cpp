#include "stdafx.h"
#include "TD3DWindow.h"

class TD3DWindow;

extern void LoadRenderConfig();



int main()
{
	
	
	LoadRenderConfig();
	
	TD3DWindow Window;
	
	if(Window.CreateD3DWindow(0,0,1440,900))
	{
		Window.EnterLoop();
	}
	
	
	
	
	
	
	
	return 0;
}
