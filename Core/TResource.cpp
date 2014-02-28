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

int TResource::CreateResource()
{
	int result;
	Shader=new TShader(Device);
	TCHAR* ShaderName=L"..\\Resource\\shaders\\BoxShader.hlsl";
	Shader->CreateShaders(ShaderName,ShaderName,"VS","PS");

	Texture = new TTexture(Device);
	result=Texture->CreateTexture(L"..\\Resource\\texture\\circular_bokeh_sharp.dds");
	assert(result);

	UINT size;
	Buffer = new TBuffer(Device);
	Buffer->CreateInputLayout(Shader,LAYOUTTYPE_POSITIONTEX0);

	size=GetBoxVertexDataSize();
	printf("(%d)\n",size);
	Buffer->CreateVertexBuffer(GetBoxVertexData(),size,sizeof(VERTEX_POSITIONTEX),false,false);
	
	size=GetBoxIndexDataSize();
	Buffer->CreateIndexBuffer(GetBoxIndexData(),size,sizeof(WORD),false);

	return 1;
}

void TResource::PostResource()
{
	Shader->PostEffect();
	Texture->PostTexture();
	Buffer->PostResource();
}

void TResource::Release()
{
}
