#include "stdafx.h"
#include "LayoutDefinitions.h"

static D3D11_INPUT_ELEMENT_DESC PositionDesc[] = {
	{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

D3D11_INPUT_ELEMENT_DESC PositionTexDesc[] =
{
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

static D3D11_INPUT_ELEMENT_DESC* DescArray[]={
	PositionDesc,
	PositionTexDesc,
};

static UINT DescArraySizes[]={
	ARRAYSIZE(PositionDesc),
	ARRAYSIZE(PositionTexDesc),
};

D3D11_INPUT_ELEMENT_DESC* GetLayoutDescArray(INPUTELEMENTDESCTYPE type)
{
	UINT index=(UINT)type;
	assert(index<ARRAYSIZE(DescArray));
	return DescArray[index];
}

UINT GetLayoutDescArraySize(INPUTELEMENTDESCTYPE type)
{
	UINT index=(UINT)type;
	assert(index<ARRAYSIZE(DescArraySizes));
	return DescArraySizes[index];
}



