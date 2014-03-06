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

VERTEX_POSITIONTEX BoxData0[] =
{
	{  -1.0f, 1.0f, -1.0f , 0.0f, 0.0f  },
	{  1.0f, 1.0f, -1.0f ,  1.0f, 0.0f },
	{  1.0f, 1.0f, 1.0f ,  1.0f, 1.0f  },
	{  -1.0f, 1.0f, 1.0f, 0.0f, 1.0f  },

	{  -1.0f, -1.0f, -1.0f, 0.0f, 0.0f  },
	{  1.0f, -1.0f, -1.0f ,  1.0f, 0.0f  },
	{  1.0f, -1.0f, 1.0f ,  1.0f, 1.0f  },
	{  -1.0f, -1.0f, 1.0f, 0.0f, 1.0f  },

	{  -1.0f, -1.0f, 1.0f,  0.0f, 0.0f  },
	{  -1.0f, -1.0f, -1.0f ,  1.0f, 0.0f  },
	{  -1.0f, 1.0f, -1.0f ,  1.0f, 1.0f  },
	{  -1.0f, 1.0f, 1.0f ,  0.0f, 1.0f },

	{  1.0f, -1.0f, 1.0f ,  0.0f, 0.0f },
	{  1.0f, -1.0f, -1.0f, 1.0f, 0.0f  },
	{  1.0f, 1.0f, -1.0f , 1.0f, 1.0f  },
	{  1.0f, 1.0f, 1.0f ,  0.0f, 1.0f  },

	{  -1.0f, -1.0f, -1.0f , 0.0f, 0.0f },
	{  1.0f, -1.0f, -1.0f ,  1.0f, 0.0f },
	{  1.0f, 1.0f, -1.0f ,  1.0f, 1.0f  },
	{  -1.0f, 1.0f, -1.0f , 0.0f, 1.0f  },

	{  -1.0f, -1.0f, 1.0f , 0.0f, 0.0f  },
	{  1.0f, -1.0f, 1.0f , 1.0f, 0.0f  },
	{  1.0f, 1.0f, 1.0f ,  1.0f, 1.0f  },
	{  -1.0f, 1.0f, 1.0f , 0.0f, 1.0f  },
};

WORD BoxIndices0[] =
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

VERTEX_POSITIONTEX BoxData1[] =
{
	{  -6.0f, 0.0f, 0.0f , 0.0f, 0.0f  },
	{  6.0f, 0.0f, 0.0f ,  1.0f, 0.0f },
	{  6.0f, 6.0f, 0.0f ,  1.0f, 1.0f  },
	{  -6.0f, 6.0f, 6.0f,  0.0f, 1.0f  }
};

WORD BoxIndices1[] =
{
	3,1,0,
	2,1,3
};

static UINT BoxVertexDataSize1=ARRAYSIZE(BoxData1);

static UINT BoxIndexDataSize1=ARRAYSIZE(BoxIndices1);

VERTEX_POSITIONTEX* GetBoxVertexData()
{
	return BoxData1;
}

WORD* GetBoxIndexData()
{
	return BoxIndices1;
}

UINT GetBoxVertexDataSize()
{
	return BoxVertexDataSize1;
}

UINT GetBoxIndexDataSize()
{
	return BoxIndexDataSize1;
}

