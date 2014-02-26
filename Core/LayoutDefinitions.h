#pragma once

typedef enum INPUTELEMENTDESC
{
	LAYOUTTYPE_POSITION                = 0,
	LAYOUTTYPE_POSITIONNORMAL          = 1,
	LAYOUTTYPE_POSITIONNORMALTEX0      = 2,
	LAYOUTTYPE_POSITIONNORMALTEX0TEX1  = 3
}INPUTELEMENTDESC;

D3D11_INPUT_ELEMENT_DESC* GetInputElementDesc(INPUTELEMENTDESC desc); 
