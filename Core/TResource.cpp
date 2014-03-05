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
	
	TCHAR* filename=L"..\\Resource\\shaders\\MainShader.hlsl";
	Shader->SetLayoutType(LAYOUTTYPE_POSITIONTEX0);
	Shader->CreateVertexShader(filename,"VS","vs_5_0");
	Shader->CreatePixelShader(filename,"PS","ps_5_0");
	Shader->InitConstantBuffer();
	
	Texture = new TTexture();
	result=Texture->CreateTexture(L"..\\Resource\\textures\\distant_cloud_higher.dds");
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
	SAFE_DELETERELEASE(Shader);
	SAFE_DELETERELEASE(Texture);
	SAFE_DELETERELEASE(Buffer);
	SAFE_DELETERELEASE(EffectShader);
}
