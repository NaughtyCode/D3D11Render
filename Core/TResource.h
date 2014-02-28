#pragma once

#include "TShader.h"
#include "TBuffer.h"
#include "TD3DDevice.h"
#include "TEffectShader.h"
#include "TTexture.h"


class TD3DDevice;
class TShader;
class TBuffer;
class TEffectShader;
class TTexture;



class TResource
{
public:
	TResource(TD3DDevice* device);
	~TResource();
	int CreateResource(const TCHAR* vsfile,const TCHAR* psfile);
	int CreateResource();
	void PostResource();
	void Release();

private:
	TD3DDevice*     Device;
	TShader*        Shader;
	TBuffer*        Buffer;
	TEffectShader*  EffectShader;
	TTexture*       Texture;
};
