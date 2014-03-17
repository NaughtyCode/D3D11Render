#include "stdafx.h"
#include "TResource.h"
#include "RenderData.h"
#include "LoadResource.h"


TResource::TResource():
	Shader(0), 
	Buffer(0),
	EffectShader(0),
	Texture(0),
	RenderContent()
{
	
}

TResource::~TResource()
{
	
}

int TResource::CreateResource()
{
	int result;
	result=RenderContent.LoadResource("..\\Resource\\Entitys\\rect.ini");
	if(result)
	{
		Shader=new TShader();
		std::string VertexShaderFile(RenderContent.VertexShaderFile);
		
		GetResourceDirASCII(VertexShaderFile);
		Shader->SetLayoutType(LAYOUTTYPE_POSITIONTEX0);
		
		Shader->CreateVertexShader(VertexShaderFile.c_str(),
					RenderContent.VertexShaderEntry,
					RenderContent.VertexShaderShaderModel);
		
		
		std::string PixelShaderFile(RenderContent.PixelShaderFile);
		GetResourceDirASCII(PixelShaderFile);
		
		Shader->CreatePixelShader(PixelShaderFile.c_str(),
					RenderContent.PixelShaderEntry,
					RenderContent.PixelShaderShaderModel);
		
		Shader->InitConstantBuffer();
		
		Texture = new TTexture();
		
		std::string TextureFile(RenderContent.TextureFile);
		GetResourceDirASCII(TextureFile);
		
		result=Texture->CreateTexture(TextureFile.c_str());
		assert(result);
		
		UINT size;
		Buffer = new TBuffer();
		
		size=GetBoxVertexDataSize();
		Buffer->CreateVertexBuffer(GetBoxVertexData(),size,sizeof(VERTEX_POSITIONTEX),false,false);
		
		size=GetBoxIndexDataSize();
		Buffer->CreateIndexBuffer(GetBoxIndexData(),size,sizeof(WORD),false);
	}
	
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

BOOL TRenderContents::LoadResource(const char* Resource)
{
	if (ParseResourceFile(Resource,(ProcessCallBackType)LoadHandler,(void*)this))
	{
		printf("解析资源文件失败(%s)\n",Resource);
		return FALSE;
	}
	this->DumpContentsInfo();
	return TRUE;
}

BOOL TRenderContents::ReadData(const char* SectionName, const char* ItemName, char* Data)
{
	#define LocalItemCheck(Section,Item) this->ItemCheck(SectionName,Section,ItemName,Item)
	if (LocalItemCheck("Textures", "Text1"))
	{
		int Size = strlen(Data);
		assert(Size<256);
		this->CopyItem(this->TextureFile,Data,Size);
	}
	else if (LocalItemCheck("VertexShader", "File"))
	{
		int Size = strlen(Data);
		assert(Size<256);
		this->CopyItem(this->VertexShaderFile,Data,Size);
	}
	else if (LocalItemCheck("VertexShader", "Entry"))
	{
		int Size = strlen(Data);
		assert(Size<64);
		this->CopyItem(this->VertexShaderEntry,Data,Size);
	}
	else if (LocalItemCheck("VertexShader", "ShaderModel"))
	{
		int Size = strlen(Data);
		assert(Size<32);
		this->CopyItem(this->VertexShaderShaderModel,Data,Size);
	}
	else if (LocalItemCheck("PixelShader", "File"))
	{
		int Size = strlen(Data);
		assert(Size<256);
		this->CopyItem(this->PixelShaderFile,Data,Size);
	}
	else if (LocalItemCheck("PixelShader", "Entry"))
	{
		int Size = strlen(Data);
		assert(Size<64);
		this->CopyItem(this->PixelShaderEntry,Data,Size);
	}
	else if (LocalItemCheck("PixelShader", "ShaderModel"))
	{
		int Size = strlen(Data);
		assert(Size<32);
		this->CopyItem(this->PixelShaderShaderModel,Data,Size);
	}
	else
	{
		return FALSE;
	}
	#undef LocalItemCheck
	return TRUE;
}

BOOL TRenderContents::ItemCheck(const char* SectionName,
			const char* CheckSectionName,
			const char* ItemName,
			const char* CheckItemName)
{
	return (strcmp(SectionName,CheckSectionName)==0 && strcmp(ItemName,CheckItemName)==0);
}

void TRenderContents::CopyItem(void* Dst,void* Src,int Size)
{
	memcpy(Dst,Src,Size);
	char* Data = (char*)Dst;
	Data[Size]='\0';
}

void TRenderContents::DumpContentsInfo()
{
	printf("-----------------------\n");
	
	
	printf("TextureFile=%s\n",             this->TextureFile);
	printf("VertexShaderFile=%s\n",        this->VertexShaderFile);
	printf("VertexShaderEntry=%s\n",       this->VertexShaderEntry);
	printf("VertexShaderShaderModel=%s\n", this->VertexShaderShaderModel);
	printf("PixelShaderFile=%s\n",         this->PixelShaderFile);
	printf("PixelShaderEntry=%s\n",        this->PixelShaderEntry);
	printf("PixelShaderShaderModel=%s\n",  this->PixelShaderShaderModel);
	
	
	printf("-----------------------\n");
}


