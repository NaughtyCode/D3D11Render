#ifndef CORE_H
#define CORE_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TDevice.h"
#include "TD3D11Render.h"
#include "TCamera.h"




extern TD3D11Render*        GRender;
extern TCamera*        GCamera;
extern TDevice*        GDevice;
extern DWORD           GGPUFrameTime;
extern char*           ResourceRoot;

void CreateRender(HWND hWnd);
void DestroyRender();

void GetResourceDirASCII(std::string& FileName);
void GetResourceDirWCHAR(std::wstring& FileName);


#define CONSTANTBUFFERMETASIZE 16

enum TextureAddressModeType
{
    AM_WRAP = 0x00,
    AM_CLAMP,
    AM_MIRROR,
    AM_BORDER
};

enum ShaderType
{
    ST_VertexShader = 0x00,
    ST_HullShader,
    ST_DomainShader,
    ST_ComputeShader,
    ST_GeometryShader,
    ST_PixelShader,
};

//Vertex Definitions

enum { MaxVertexElementCount = 16 };

enum TVertexElementType
{
    ELEMENTTYPE_FLOAT1 = 0X00,
    ELEMENTTYPE_FLOAT2,
    ELEMENTTYPE_FLOAT3,
    ELEMENTTYPE_FLOAT4,
    ELEMENTTYPE_PACKEDNORMAL,
    ELEMENTTYPE_UBYTE4,
    ELEMENTTYPE_UBYTE4N,
    ELEMENTTYPE_COLOR,
    ELEMENTTYPE_SHORT2,
    ELEMENTTYPE_SHORTN,
    ELEMENTTYPE_HALF2,
};

enum TVertexElementSemanticName
{
    SEMANTICNAME_POSITION = 0X00,
    SEMANTICNAME_TEXTURECOORDINATE,
    SEMANTICNAME_BLENDWEIGHT,
    SEMANTICNAME_BLENDINDICES,
    SEMANTICNAME_NORMAL,
    SEMANTICNAME_TANGENT,
    SEMANTICNAME_BINORMAL,
    SEMANTICNAME_COLOR,
};



class TVertexElement
{
public:
    BYTE StreamIndex;
    BYTE Offset;
    BYTE Type;
    BYTE Usage;
    BYTE UsageIndex;
    BOOL bUseInstanceIndex;
    UINT NumVerticesPerInstance;
    
    TVertexElement() {}
    
    TVertexElement(BYTE InStreamIndex,
        BYTE InOffset,
        BYTE InType,
        BYTE InUsage,
        BYTE InUsageIndex,
        BOOL bInUseInstanceIndex=FALSE,
        UINT InNumVerticesPerInstance=0):
        StreamIndex(InStreamIndex),
        Offset(InOffset),
        Type(InType),
        Usage(InUsage),
        UsageIndex(InUsageIndex),
        bUseInstanceIndex(bInUseInstanceIndex),
        NumVerticesPerInstance(InNumVerticesPerInstance)
    {
        
    }
    
    void operator=(const TVertexElement& In)
    {
        StreamIndex            = In.StreamIndex;
        Offset                 = In.Offset;
        Type                   = In.Type;
        Usage                  = In.Usage;
        UsageIndex             = In.UsageIndex;
        bUseInstanceIndex      = In.bUseInstanceIndex;
        NumVerticesPerInstance = In.NumVerticesPerInstance;
    }
};

typedef std::vector< TVertexElement > TVertexElementArray;

class TVertexDeclaration
{
public:
    TVertexDeclaration(const TVertexElementArray& Elements);
    D3D11_INPUT_ELEMENT_DESC ElemetArray[MaxVertexElementCount];
};

void GDrawFrame();
void GStartFrame();
void GEndFrame();

#endif