#include "stdafx.h"
#include "TResource.h"

TResource::TResource(TD3DDevice* device) :Device(device), Shader(0), RenderResource(0)
{
}

TResource::~TResource()
{
}

int TResource::CreateResource()
{
	int rt;
	Shader = new TShader(Device);
	assert(Shader);
	rt = Shader->CreateShaders(L"..\\shaders\\vertexshader.hlsl", L"..\\shaders\\pixelshader.hlsl", "VSMain", "PSMain");
	assert(rt);
	RenderResource = new TRenderResource(Device,Shader);
	assert(RenderResource);
	rt = RenderResource->CreateRenderResource();
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
