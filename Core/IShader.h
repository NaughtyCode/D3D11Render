#pragma once

class IShader
{
public:
	IShader();
	virtual ~IShader();
	virtual void PostEffect()=0;
	virtual LPVOID GetVSBufferPointer()=0;
	virtual SIZE_T GetVSBufferSize()=0;
	virtual void Release()=0;
};
