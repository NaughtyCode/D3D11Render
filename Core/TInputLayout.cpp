#include "stdafx.h"
#include "TInputLayout.h"


TInputLayout::TInputLayout(TD3DDevice* device):
								Device(device),
								Layout(0)
{

}

TInputLayout::~TInputLayout(void)
{

}

int TInputLayout::CreateInputLayout(IShader* shader,INPUTELEMENTDESCTYPE type)
{
	D3D11_INPUT_ELEMENT_DESC* desc = GetLayoutArray(type);
	UINT Num = GetLayoutArraySize(type);
	if (FAILED(Device->GetDevice()->CreateInputLayout(desc,
		Num,
		shader->GetShaderBufferPointer(),
		shader->GetShaderBufferSize(),
		&Layout)))
	{
		return 0;
	}
	return 1;
}

void TInputLayout::PostInputLayout()
{
	Device->GetImmediateContext()->IASetInputLayout(Layout);
}

void TInputLayout::Release()
{
	SAFE_RELEASE(Layout);
}

