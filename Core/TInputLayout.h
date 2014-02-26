#pragma once
#include "TD3DDevice.h"
#include "TShader.h"
#include "TEffectShader.h"
#include "LayoutDefinitions.h"

class TInputLayout
{
public:
	TInputLayout(TD3DDevice* device);
	~TInputLayout(void);
	int CreateInputLayout(TShader* shader,INPUTELEMENTDESC type);
	int CreateInputLayout(TEffectShader* shader,INPUTELEMENTDESC type);
	void PostInputLayout();
	void Release();

private:
	TD3DDevice* Device;
	ID3D11InputLayout* VertexLayout;
};



