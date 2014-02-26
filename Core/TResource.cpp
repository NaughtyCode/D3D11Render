#include "stdafx.h"
#include "TResource.h"

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
	int rt;
	/*Shader = new TShader(Device);
	assert(Shader);
	rt = Shader->CreateShaders(vsfile,psfile,"VSMain","PSMain");
	assert(rt);
	*/
	EffectShader=new TEffectShader(Device);
	assert(EffectShader);
	EffectShader->CreateEffectShader(L"..\\Resource\\shaders\\PrimitiveEffectFramework.hlsl");

	Buffer = new TBuffer(Device);
	assert(Buffer);
	rt = Buffer->CreateVertexBuffer(EffectShader);
	assert(rt);

	return 1;
}

void TResource::PostResource()
{
	EffectShader->PostEffectShader();
	Buffer->PostRenderResource();
}

void TResource::Release()
{

}
