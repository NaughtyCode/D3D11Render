#ifndef RENDERUTILS_H
#define RENDERUTILS_H

#if _MSC_VER > 1000
# pragma once
#endif

BOOL CheckConstantBufferSize(UINT Size);

UINT AlignToBlock(UINT Size,UINT Align);

void DumpReturnErrorText(HRESULT hr);

#endif



