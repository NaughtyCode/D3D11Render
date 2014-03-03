#include "stdafx.h"
#include "RenderUtils.h"

#define CONSTANTBUFFERMETASIZE 16

BOOL CheckConstantBufferSize(UINT Size)
{
	if(Size <= D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT && (Size % CONSTANTBUFFERMETASIZE) == 0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


UINT AlignToBlock(UINT Size,UINT Align)
{
	assert(Align>0);
	
	UINT NewSize;
	UINT Remain=Size%Align;
	if(Remain==0)
	{
		NewSize = Remain*Align;
	}else
	{
		NewSize = (Remain+1)*Align;
	}
	return NewSize;
}


void DumpReturnErrorText(HRESULT hr)
{
	switch (hr)
	{
	case D3D11_ERROR_FILE_NOT_FOUND:
		printf("D3D11_ERROR_FILE_NOT_FOUND\n");
		break;
	case D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS:
		printf("D3D11_ERROR_TOO_MANY_UNIQUE_STATE_OBJECTS\n");
		break;
	case D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS:
		printf("D3D11_ERROR_TOO_MANY_UNIQUE_VIEW_OBJECTS\n");
		break;
	case D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD:
		printf("D3D11_ERROR_DEFERRED_CONTEXT_MAP_WITHOUT_INITIAL_DISCARD\n");
		break;
	case D3DERR_INVALIDCALL:
		printf("D3DERR_INVALIDCALL\n");
		break;
	case E_FAIL:
		printf("E_FAIL\n");
		break;
	case E_INVALIDARG:
		printf("E_INVALIDARG\n");
		break;
	case E_OUTOFMEMORY:
		printf("E_OUTOFMEMORY\n");
		break;
	case E_NOTIMPL:
		printf("E_NOTIMPL\n");
		break;
	case S_FALSE:
		printf("S_FALSE\n");
		break;
	case S_OK:
		printf("S_OK\n");
		break;
	}
}







