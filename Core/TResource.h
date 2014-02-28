#pragma once

#include "TShader.h"
#include "TBuffer.h"
#include "TD3DDevice.h"
#include "TEffectShader.h"

class TD3DDevice;
class TShader;
class TBuffer;
class TEffectShader;

class TResource
{
public:
	TResource(TD3DDevice* device);
	~TResource();
	int CreateResource(const WCHAR* vsfile,const WCHAR* psfile);
	void PostResource();
	void Release();
private:
	TD3DDevice* Device;
	TShader* Shader;
	TBuffer* Buffer;
	TEffectShader*  EffectShader;
};
