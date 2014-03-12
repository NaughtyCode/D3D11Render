#ifndef TSHADER_H
#define TSHADER_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "Core.h"
#include "TDevice.h"
#include "Definitions.h"
#include "TConstantBuffer.h"


class IShader;
class TDevice;
class TConstantBuffer;

class IShader
{
public:
	IShader(){}
	virtual ~IShader(){}
	virtual void PostEffect()=0;
	virtual LPVOID GetShaderBufferPointer()=0;
	virtual SIZE_T GetShaderBufferSize()=0;
	virtual void Release()=0;
};


class TShader:public IShader
{
public:
	TShader();
	~TShader();
	int CompileShaderFromFile(const char* filename,
				LPCSTR entry,
				LPCSTR shadermodel,
				ID3DBlob** ppBlobOut);
	
	int CreateVertexShader(const char* filename,
			       const char* entry,
			       const char* shadermodel);
	
	int CreatePixelShader(const char* filename,
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
	ID3D11HullShader*       HullShader;
	ID3D11DomainShader*     DomainShader;
	ID3D11GeometryShader*   GeometryShader;
	ID3D11InputLayout*      InputLayout;
	ID3D11VertexShader*     VertexShader;
	ID3D11PixelShader*      PixelShader;
	ID3DBlob*               VertexShaderBuffer;
	ID3DBlob*               PixelShaderBuffer;
	TConstantBuffer*        ShaderResource;
	ID3D11DeviceContext*    DeviceContext;
	INPUTTYPE_TYPE          LayoutType;
	
};

#endif



