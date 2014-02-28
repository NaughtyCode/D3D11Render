#pragma once
#include "TD3DDevice.h"
#include "TShader.h"
#include "TEffectShader.h"
#include "LayoutDefinitions.h"
#include "IShader.h"

class IShader;

class TInputLayout
{
public:
	TInputLayout(TD3DDevice* device);
	~TInputLayout(void);
	int CreateInputLayout(IShader* shader,INPUTELEMENTDESCTYPE type);
	void PostInputLayout();
	void Release();

private:
	TD3DDevice* Device;
	ID3D11InputLayout* Layout;
};



