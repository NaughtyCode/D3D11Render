#include "stdafx.h"
#include "RenderData.h"

static VERTEX_POSITION RectData[]=
{
	0.0,0.0,0.0,
	0.0,0.5,0.0,
	0.5,0.5,0.0,
	0.5,0.5,0.0,
	0.5,0.0,0.0,
	0.0,0.0,0.0,
}; 

static UINT RectDataSize=ARRAYSIZE(RectData);

VERTEX_POSITION* GetRectData()
{
	return RectData;
}

UINT GetRectDataSize()
{
	return RectDataSize;
}

VERTEX_POSITIONTEX BoxData[] =
{
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, -1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, -1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, -1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, -1.0f ), XMFLOAT2( 0.0f, 1.0f ) },

	{ XMFLOAT3( -1.0f, -1.0f, 1.0f ), XMFLOAT2( 0.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, -1.0f, 1.0f ), XMFLOAT2( 1.0f, 0.0f ) },
	{ XMFLOAT3( 1.0f, 1.0f, 1.0f ), XMFLOAT2( 1.0f, 1.0f ) },
	{ XMFLOAT3( -1.0f, 1.0f, 1.0f ), XMFLOAT2( 0.0f, 1.0f ) },
};

//
//VERTEX_POSITIONTEX BoxData[] =
//{
//	{ ( -1.0f, 1.0f, -1.0f ), ( 0.0f, 0.0f ) },
//	{ ( 1.0f, 1.0f, -1.0f ), ( 1.0f, 0.0f ) },
//	{ ( 1.0f, 1.0f, 1.0f ), ( 1.0f, 1.0f ) },
//	{ ( -1.0f, 1.0f, 1.0f ), ( 0.0f, 1.0f ) },
//
//	{ ( -1.0f, -1.0f, -1.0f ), ( 0.0f, 0.0f ) },
//	{ ( 1.0f, -1.0f, -1.0f ), ( 1.0f, 0.0f ) },
//	{ ( 1.0f, -1.0f, 1.0f ), ( 1.0f, 1.0f ) },
//	{ ( -1.0f, -1.0f, 1.0f ), ( 0.0f, 1.0f ) },
//
//	{ ( -1.0f, -1.0f, 1.0f ), ( 0.0f, 0.0f ) },
//	{ ( -1.0f, -1.0f, -1.0f ), ( 1.0f, 0.0f ) },
//	{ ( -1.0f, 1.0f, -1.0f ), ( 1.0f, 1.0f ) },
//	{ ( -1.0f, 1.0f, 1.0f ), ( 0.0f, 1.0f ) },
//
//	{ ( 1.0f, -1.0f, 1.0f ), ( 0.0f, 0.0f ) },
//	{ ( 1.0f, -1.0f, -1.0f ), ( 1.0f, 0.0f ) },
//	{ ( 1.0f, 1.0f, -1.0f ), ( 1.0f, 1.0f ) },
//	{ ( 1.0f, 1.0f, 1.0f ), ( 0.0f, 1.0f ) },
//
//	{ ( -1.0f, -1.0f, -1.0f ), ( 0.0f, 0.0f ) },
//	{ ( 1.0f, -1.0f, -1.0f ), ( 1.0f, 0.0f ) },
//	{ ( 1.0f, 1.0f, -1.0f ), ( 1.0f, 1.0f ) },
//	{ ( -1.0f, 1.0f, -1.0f ), ( 0.0f, 1.0f ) },
//
//	{ ( -1.0f, -1.0f, 1.0f ), ( 0.0f, 0.0f ) },
//	{ ( 1.0f, -1.0f, 1.0f ), ( 1.0f, 0.0f ) },
//	{ ( 1.0f, 1.0f, 1.0f ), ( 1.0f, 1.0f ) },
//	{ ( -1.0f, 1.0f, 1.0f ), ( 0.0f, 1.0f ) },
//};

static UINT BoxVertexDataSize=ARRAYSIZE(BoxData);

WORD BoxIndices[] =
{
	3,1,0,
	2,1,3,

	6,4,5,
	7,4,6,

	11,9,8,
	10,9,11,

	14,12,13,
	15,12,14,

	19,17,16,
	18,17,19,

	22,20,21,
	23,20,22
};

static UINT BoxIndexDataSize=ARRAYSIZE(BoxIndices);

VERTEX_POSITIONTEX* GetBoxVertexData()
{
	return BoxData;
}

UINT GetBoxVertexDataSize()
{
	return BoxVertexDataSize;
}

WORD* GetBoxIndexData()
{
	return BoxIndices;
}

UINT GetBoxIndexDataSize()
{
	return BoxIndexDataSize;
}

