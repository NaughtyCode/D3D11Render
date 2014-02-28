#include "stdafx.h"
#include "LayoutDefinitions.h"

static D3D11_INPUT_ELEMENT_DESC PositionElementDesc[] = {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC* AllInputElementDesc[]={
	PositionElementDesc,
};

static UINT AllInputElementDescArraySize[]={
	ARRAYSIZE(PositionElementDesc),
};

D3D11_INPUT_ELEMENT_DESC* GetInputElementDesc(INPUTELEMENTDESCTYPE type)
{
	switch (type)
	{
	case LAYOUTTYPE_POSITION:
		return AllInputElementDesc[0];
		break;
	case LAYOUTTYPE_POSITIONNORMAL:
		return AllInputElementDesc[1];
		break;
	case LAYOUTTYPE_POSITIONNORMALTEX0:
		return AllInputElementDesc[2];
		break;
	case LAYOUTTYPE_POSITIONNORMALTEX0TEX1:
		return AllInputElementDesc[3];
		break;
	default:
		return 0;
	}
}

UINT GetInputElementDescSize(INPUTELEMENTDESCTYPE type)
{
	switch (type)
	{
	case LAYOUTTYPE_POSITION:
		return AllInputElementDescArraySize[0];
		break;
	case LAYOUTTYPE_POSITIONNORMAL:
		return AllInputElementDescArraySize[1];
		break;
	case LAYOUTTYPE_POSITIONNORMALTEX0:
		return AllInputElementDescArraySize[2];
		break;
	case LAYOUTTYPE_POSITIONNORMALTEX0TEX1:
		return AllInputElementDescArraySize[3];
		break;
	default:
		return 0;
	}
}




