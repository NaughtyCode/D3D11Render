#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#if _MSC_VER > 1000
# pragma once
#endif

BOOL CheckConstantBufferSize(UINT Size);

UINT AlignToBlock(UINT Size,UINT Align);

std::string GetErrorString(HRESULT error);

void VerifyResult(HRESULT error,const char* Code,const char* Filename,UINT Line);

#define VERIFYRESULT(error) VerifyResult(error,#error,__FILE__,__LINE__);

#endif



