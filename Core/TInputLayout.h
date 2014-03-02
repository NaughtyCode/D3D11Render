#ifndef TINPUTLAYOUT_H
#define TINPUTLAYOUT_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "TD3DDevice.h"
#include "TShader.h"
#include "TEffectShader.h"
#include "Definitions.h"
#include "IShader.h"

class IShader;

class TInputLayout
{
public:
    TInputLayout(TD3DDevice* device);
    ~TInputLayout(void);
    int CreateInputLayout(IShader* shader,INPUTTYPE_TYPE type);
    void PostInputLayout();
    void Release();
    
private:
    TD3DDevice*        Device;
    ID3D11InputLayout* Layout;
};


#endif
