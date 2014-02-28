#pragma once
#include "IShader.h"
#include "TD3DDevice.h"

class IShader;
class TD3DDevice;

struct CBNeverChanges
{
	XMMATRIX mView;
};

struct CBChangeOnResize
{
	XMMATRIX mProjection;
};

struct CBChangesEveryFrame
{
	XMMATRIX mWorld;
	XMFLOAT4 vMeshColor;
};

class TShader:public IShader
{
public:
	TShader(TD3DDevice* device);
	~TShader();
	int CompileShaderFromFile(const WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);
	int CreateShaders(const WCHAR* VSFilename, const WCHAR* PSFilename, const char* vs, const char* ps);
	int CreateConstantBuffer();
	int CreateSampler();
	void UpdateConstantBuffer();
	void UpdateConstantBufferFrame();
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
	ID3D11Buffer*           ConstantBufferNeverChanges;
	ID3D11Buffer*           ConstantBufferChangeOnResize;
	ID3D11Buffer*           ConstantBufferChangesEveryFrame;
	ID3D11SamplerState*     Sampler;
	XMFLOAT4                MeshColor;
};


