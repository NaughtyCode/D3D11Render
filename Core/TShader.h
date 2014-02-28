#pragma once
#include "IShader.h"
#include "TD3DDevice.h"

class IShader;
class TD3DDevice;

class TShader:public IShader
{
public:
	TShader(TD3DDevice* device);
	~TShader();
	int CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	int CreateShaders(const WCHAR* VSFilename, const WCHAR* PSFilename, const char* vs, const char* ps);
	virtual void PostEffect();
	virtual LPVOID GetVSBufferPointer();
	virtual SIZE_T GetVSBufferSize();
	virtual void Release();
private:
	TD3DDevice*             Device;
	ID3D11VertexShader*     VertexShader;
	ID3D11PixelShader*      PixelShader;
	ID3DBlob*               VertexShaderBuffer;
	ID3DBlob*               PixelShaderBuffer;
};

