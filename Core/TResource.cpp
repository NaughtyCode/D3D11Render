#include "stdafx.h"
#include "TResource.h"
#include "RenderData.h"

TResource::TResource():
	Shader(0), 
	Buffer(0),
	EffectShader(0),
	Texture(0)
{
}

TResource::~TResource()
{
}

int TResource::CreateResource()
{
	int result;
	Shader=new TShader();
	std::string FileName;
	FileName="shaders\\MainShader.hlsl";
	GetResourceDirASCII(FileName);
	Shader->SetLayoutType(LAYOUTTYPE_POSITIONTEX0);
	Shader->CreateVertexShader(FileName.c_str(),"VS","vs_5_0");
	Shader->CreatePixelShader(FileName.c_str(),"PS","ps_5_0");
	Shader->InitConstantBuffer();
	
	Texture = new TTexture();
	FileName="textures\\distanceclouds.dds";
	GetResourceDirASCII(FileName);
	result=Texture->CreateTexture(FileName.c_str());
	assert(result);
	
	UINT size;
	Buffer = new TBuffer();
	
	size=GetBoxVertexDataSize();
	Buffer->CreateVertexBuffer(GetBoxVertexData(),size,sizeof(VERTEX_POSITIONTEX),false,false);
	
	size=GetBoxIndexDataSize();
	Buffer->CreateIndexBuffer(GetBoxIndexData(),size,sizeof(WORD),false);
	
	return 1;
}

void TResource::CreateResource(const TCHAR* resourcefile)
{
	
}

void TResource::CreateResource(const char* resourcefile)
{
	
}

void TResource::PostResource()
{
	Shader->PostEffect();
	Texture->PostTexture();
	Buffer->PostResource();
}

void TResource::Release()
{
	SAFE_RELEASEDELETE(Shader);
	SAFE_RELEASEDELETE(Texture);
	SAFE_RELEASEDELETE(Buffer);
}
