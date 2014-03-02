#pragma once

class IShader
{
public:
	IShader();
	virtual ~IShader();
	virtual void PostEffect()=0;
	virtual LPVOID GetShaderBufferPointer()=0;
	virtual SIZE_T GetShaderBufferSize()=0;
	virtual void Release()=0;
};
