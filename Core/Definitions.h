#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#if _MSC_VER > 1000
# pragma once
#endif

#define CONSTANTBUFFERMETASIZE 16

enum TextureAddressModeType
{
	TAM_WRAP,
	TAM_CLAMP,
	TAM_MIRROR,
	TAM_BORDER
};

typedef struct VERTEX_POSITION{
	FLOAT x;
	FLOAT y;
	FLOAT z;
}VERTEX_POSITION;

typedef struct VERTEX_POSITIONTEX
{
	FLOAT x;
	FLOAT y;
	FLOAT z;
	FLOAT u;
	FLOAT v;
}VERTEX_POSITIONTEX;

typedef enum INPUTTYPE_TYPE
{
	LAYOUTTYPE_UNKNOWN  = -1,
	LAYOUTTYPE_POSITION = 0,
	LAYOUTTYPE_POSITIONTEX0,
	LAYOUTTYPE_POSITIONTEX0TEX1,
	LAYOUTTYPE_POSITIONNORMAL,
	LAYOUTTYPE_POSITIONNORMALTEX0,
	LAYOUTTYPE_POSITIONNORMALTEX0TEX1,
}INPUTTYPE_TYPE;




D3D11_INPUT_ELEMENT_DESC* GetLayoutArray(INPUTTYPE_TYPE type); 

UINT GetLayoutArraySize(INPUTTYPE_TYPE type); 


#endif