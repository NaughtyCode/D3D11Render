#ifndef TSHADER_H
#define TSHADER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "IShader.h"
#include "TD3DDevice.h"
#include "Definitions.h"
#include "TConstantBuffer.h"


class IShader;
class TD3DDevice;
class TConstantBuffer;

typedef struct TCommonShaderResource
{
	XMMATRIX matrix;
}TCommonShaderResource;

class TShader:public IShader
{
public:
	TShader(TD3DDevice* device);
	~TShader();
	int CompileShaderFromFile(const TCHAR* filename,
				LPCSTR entry,
				LPCSTR shadermodel,
				ID3DBlob** ppBlobOut);
	
	int CreateVertexShader(const TCHAR* filename,
			       const char* entry,
			       const char* shadermodel);
	
	int CreatePixelShader(const TCHAR* filename,
			      const char* entry,
			      const char* shadermodel);
	
	int InitConstantBuffer();
	
	int CreateConstantBuffer();
	
	virtual void   PostEffect();
	virtual LPVOID GetShaderBufferPointer();
	virtual SIZE_T GetShaderBufferSize();
	virtual void   Release();
	
	int CreateInputLayout();
	void SetLayoutType(INPUTTYPE_TYPE type);
	
private:
	TD3DDevice*             Device;
	ID3D11InputLayout*      InputLayout;
	ID3D11VertexShader*     VertexShader;
	ID3D11PixelShader*      PixelShader;
	ID3DBlob*               VertexShaderBuffer;
	ID3DBlob*               PixelShaderBuffer;
	TConstantBuffer*        ShaderResource;
	INPUTTYPE_TYPE          LayoutType;
};

#endif



