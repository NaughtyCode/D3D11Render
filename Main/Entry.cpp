#include "stdafx.h"
#include "TD3DWindow.h"

class TD3DWindow;

int main()
{
	TD3DWindow Window;
	if(Window.CreateD3DWindow(0,0,1440,900))
	{
		Window.SetWindowPos(200,80);
		Window.EnterLoop();
	}



	return 0;
}
