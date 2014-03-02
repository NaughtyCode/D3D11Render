#pragma once
#include "IShader.h"
#include "TD3DDevice.h"

class IShader;
class TD3DDevice;

struct CBNeverChanges
{
	XMMATRIX View;
};

struct CBChangeOnResize
{
	XMMATRIX Projection;
};

struct CBChangesEveryFrame
{
	XMMATRIX World;
	TColorF ObjectColor;
};

class TShader:public IShader
{
public:
	TShader(TD3DDevice* device);
	~TShader();
	int CompileShaderFromFile(const TCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	int CreateShaders(const TCHAR* VSFilename, const TCHAR* PSFilename, const char* vs, const char* ps);
	int CreateConstantBuffer();
	int CreateSampler();
	void UpdateConstantBuffer();
	void UpdateConstantBufferFrame();
	virtual void PostEffect();
	virtual LPVOID GetShaderBufferPointer();
	virtual SIZE_T GetShaderBufferSize();
	virtual void Release();

private:
	TD3DDevice*             Device;
	ID3D11VertexShader*     VertexShader;
	ID3D11PixelShader*      PixelShader;
	ID3DBlob*               VertexShaderBuffer;
	ID3DBlob*               PixelShaderBuffer;
	ID3D11Buffer*           ConstantBufferNeverChanges;
	ID3D11Buffer*           ConstantBufferChangeOnResize;
	ID3D11Buffer*           ConstantBufferChangesEveryFrame;
	ID3D11SamplerState*     Sampler;
	TColorF                 ObjectColor;
};


