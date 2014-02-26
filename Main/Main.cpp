#include "stdafx.h"
#include "D3DRenderWindow.h"

class D3DRenderWindow;

int main()
{
	D3DRenderWindow render;
	if(render.CreateRenderWindow()){
		render.Loop();
	}
	return 0;
}
