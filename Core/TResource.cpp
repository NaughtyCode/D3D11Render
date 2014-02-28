#include "stdafx.h"
#include "TResource.h"
#include "RenderData.h"

TResource::TResource(TD3DDevice* device) :Device(device),
	Shader(0), 
	Buffer(0),
	EffectShader(0),
	Texture(0)
{
}

TResource::~TResource()
{
}

int TResource::CreateResource(const TCHAR* vsfile,const TCHAR* psfile)
{
	return 1;
}

int TResource::CreateResource(const TCHAR* EffectFile)
{
	EffectShader=new TEffectShader(Device);
	EffectShader->CreateEffectShader(EffectFile);
	
	Texture = new TTexture(Device);
	Texture->CreateTexture(L"..\\Resource\\texture\\plastic.dds");

	Buffer = new TBuffer(Device);
	Buffer->CreateInputLayout(EffectShader);
	UINT size=GetBoxVertexDataSize();
	Buffer->CreateVertexBuffer(GetBoxVertexData(),size,sizeof(VERTEX_POSITIONTEX),false,false);
	size=GetBoxIndexDataSize();
	Buffer->CreateIndexBuffer(GetBoxIndexData(),size,false);

	return 1;
}

void TResource::PostResource()
{
	EffectShader->PostEffect();
	Texture->PostTexture();
	Buffer->PostResource();
}

void TResource::Release()
{
}
