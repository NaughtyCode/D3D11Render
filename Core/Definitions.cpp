#include "stdafx.h"
#include "Definitions.h"

static D3D11_TEXTURE_ADDRESS_MODE GetTextureAddressMode(TextureAddressModeType Mode)
{
	switch(Mode)
	{
		case AM_CLAMP:
			return D3D11_TEXTURE_ADDRESS_CLAMP;
		case AM_MIRROR:
			return D3D11_TEXTURE_ADDRESS_MIRROR;
		case AM_BORDER:
			return D3D11_TEXTURE_ADDRESS_BORDER;
		default:
			return D3D11_TEXTURE_ADDRESS_WRAP;
	};
}


static D3D11_INPUT_ELEMENT_DESC PositionLayout[] = {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

D3D11_INPUT_ELEMENT_DESC PositionTexLayout[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

D3D11_INPUT_ELEMENT_DESC PositionNormalLayout[] =
{
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
};

static D3D11_INPUT_ELEMENT_DESC* LayoutArray[] = 
{
	PositionLayout,
	PositionTexLayout,
	NULL,
	PositionNormalLayout,
	NULL,
	NULL,
};

static UINT LayoutArraySize[] = 
{
	ARRAYSIZE(PositionLayout),
	ARRAYSIZE(PositionTexLayout),
	NULL,
	ARRAYSIZE(PositionNormalLayout),
	NULL,
	NULL,
};

D3D11_INPUT_ELEMENT_DESC* GetLayoutArray(INPUTTYPE_TYPE type)
{
	UINT index=(UINT)type;
	assert(index<ARRAYSIZE(LayoutArray));
	return LayoutArray[index];
}

UINT GetLayoutArraySize(INPUTTYPE_TYPE type)
{
	UINT index=(UINT)type;
	assert(index<ARRAYSIZE(LayoutArraySize));
	return LayoutArraySize[index];
}





