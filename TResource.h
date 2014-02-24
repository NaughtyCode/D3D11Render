#pragma once

#include "TShader.h"
#include "TRenderResource.h"
#include "D3DDevice.h"

class TD3DDevice;
class TShader;
class TRenderResource;

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
	TRenderResource* RenderResource;
};
