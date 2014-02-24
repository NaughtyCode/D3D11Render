#pragma once

#include "TShader.h"
#include "TBuffer.h"
#include "D3DDevice.h"

class TD3DDevice;
class TShader;
class TBuffer;

class TResource
{
public:
	TResource(TD3DDevice* device);
	~TResource();
	int CreateResource();
	void PostResource();
	void Release();
private:
	TD3DDevice* Device;
	TShader* Shader;
	TBuffer* RenderResource;
};
