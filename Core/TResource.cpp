#include "stdafx.h"
#include "TResource.h"
#include "RenderData.h"

TResource::TResource(TD3DDevice* device) :Device(device),
	Shader(0), 
	Buffer(0),
	EffectShader(0)
{
}

TResource::~TResource()
{
}

int TResource::CreateResource(const WCHAR* vsfile,const WCHAR* psfile)
{
	EffectShader=new TEffectShader(Device);
	EffectShader->CreateEffectShader(L"..\\Resource\\shaders\\PrimitiveEffectFramework.hlsl");
	Buffer = new TBuffer(Device);
	UINT size=GetVertexDataSize();
	Buffer->CreateInputLayout(EffectShader);
	Buffer->CreateStaticVertexBuffer(size,GetVertexData());
	return 1;
}

void TResource::PostResource()
{
	EffectShader->PostEffect();
	Buffer->PostRenderResource();
}

void TResource::Release()
{
}
