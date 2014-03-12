#ifndef TCONSTANTBUFFER_H
#define TCONSTANTBUFFER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TD3DDevice.h"
#include "GlobalMath.h"




class TD3DDevice;




struct TConstantBufferContents
{
    TMatrix WorldViewProjectMatrix;
};








class TConstantBuffer
{
public:
    TConstantBuffer(UINT Size = 0,UINT NumBuffers = 1);
    ~TConstantBuffer();
    void CreateConstantBuffer();
    void UpdateBufferData(LPVOID pData, WORD Offset, WORD Size);
    BOOL UpdateConstantBufferResource(BOOL isDiscard);
    void PostConstantBuffer(UINT StartSlot,UINT NumBuffers);
    
    ID3D11Buffer* GetConstantBuffer();
    
    void Release();
    
private:
    LPID3D11Buffer* ConstantBuffers;
    UINT            MaxSize;
    BOOL            HasData;
    BYTE*           Data;
    UINT            CurrentSubBuffer;
    UINT            NumSubBuffers;
    UINT            CurrentUpdateSize;
    UINT            TotalUpdateSize;
};







#endif


