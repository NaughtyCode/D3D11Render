#include "stdafx.h"
#include "RenderData.h"

VERTEX_POSITIONTEX VertexData[] =
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

WORD IndexData[] =
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

VERTEX_POSITIONTEX* GetBoxVertexData()
{
	return VertexData;
}

WORD* GetBoxIndexData()
{
	return IndexData;
}

UINT GetBoxVertexDataSize()
{
	return ARRAYSIZE(VertexData);
}

UINT GetBoxIndexDataSize()
{
	return ARRAYSIZE(IndexData);
}

