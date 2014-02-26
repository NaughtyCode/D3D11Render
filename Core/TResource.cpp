#include "stdafx.h"
#include "TResource.h"

TResource::TResource(TD3DDevice* device) :Device(device), Shader(0), RenderResource(0)
{
}

TResource::~TResource()
{
}

int TResource::CreateResource(const WCHAR* vsfile,const WCHAR* psfile)
{
	int rt;
	Shader = new TShader(Device);
	assert(Shader);
	rt = Shader->CreateShaders(vsfile,psfile,"VSMain","PSMain");
	assert(rt);
	RenderResource = new TBuffer(Device,Shader);
	assert(RenderResource);
	rt = RenderResource->CreateVertexBuffer();
	assert(rt);
	return 1;
}

void TResource::PostResource()
{
	Shader->PostShaders();
	RenderResource->PostRenderResource();
}

void TResource::Release()
{

}
