#include "stdafx.h"
#include "RenderData.h"


static Vertex Vertices[]=
{
	0.0,0.0,0.0,
	0.0,0.5,0.0,
	0.5,0.5,0.0,
	0.5,0.5,0.0,
	0.5,0.0,0.0,
	0.0,0.0,0.0,
};    

static UINT DataSize=ARRAYSIZE(Vertices);


Vertex* GetVertexData()
{
	return Vertices;
}

UINT GetVertexDataSize()
{
	return DataSize;
}