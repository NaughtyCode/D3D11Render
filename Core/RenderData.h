#ifndef RENDERDATA_H
#define RENDERDATA_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "Definitions.h"

VERTEX_POSITION* GetRectData();
UINT GetRectDataSize();

VERTEX_POSITIONTEX* GetBoxVertexData();
UINT GetBoxVertexDataSize();
WORD* GetBoxIndexData();
UINT GetBoxIndexDataSize();


#endif

