#include "stdafx.h"
#include "TInputLayout.h"


TInputLayout::TInputLayout(TD3DDevice* device):
								Device(device),
								VertexLayout(0)
{

}

TInputLayout::~TInputLayout(void)
{

}

int TInputLayout::CreateInputLayout(TShader* shader,INPUTELEMENTDESC type)
{
	D3D11_INPUT_ELEMENT_DESC* desc = GetInputElementDesc(type);
	UINT Num = (UINT)LAYOUTTYPE_POSITION+1U;
	if (FAILED(Device->GetDevice()->CreateInputLayout(desc,Num,shader->GetVSBufferPointer(),shader->GetVSBufferSize(),&VertexLayout))){
		return 0;
	}
	return 1;
}

int TInputLayout::CreateInputLayout(TEffectShader* shader,INPUTELEMENTDESC type)
{
	D3D11_INPUT_ELEMENT_DESC* desc = GetInputElementDesc(type);

	UINT num = (UINT)LAYOUTTYPE_POSITION+1U;
	
	HRESULT hr=Device->GetDevice()->CreateInputLayout(desc,num,shader->GetVSBufferPointer(),shader->GetVSBufferSize(),&VertexLayout);
	if (FAILED(hr)){
		DumpErrorInfo(hr);
		return 0;
	}
	return 1;
}

void TInputLayout::PostInputLayout()
{
	Device->GetImmediateContext()->IASetInputLayout(VertexLayout);
}

void TInputLayout::Release()
{
	SAFE_RELEASE(VertexLayout);
}

