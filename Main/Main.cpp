#include "stdafx.h"
#include "TD3DWindow.h"

class D3DRenderWindow;

int main()
{
	TD3DWindow render;
	if(render.CreateD3DWindow()){
		render.Loop();
	}
	return 0;
}
