#include "stdafx.h"
#include "TConstantBuffer.h"


TConstantBuffer::TConstantBuffer(TD3DDevice* device,UINT Size,UINT NumBuffers) : 
	Device(device),
	MaxSize(Size),
	HasData(FALSE),
	Data(NULL),
	ConstantBuffers(NULL),
	CurrentSubBuffer(0),
	NumSubBuffers(NumBuffers),
	CurrentUpdateSize(0),
	TotalUpdateSize(0)
{
	
}

TConstantBuffer::~TConstantBuffer()
{
	this->Release();
}

void TConstantBuffer::CreateConstantBuffer()
{
	ID3D11Buffer* CBuffer = NULL;
	D3D11_BUFFER_DESC BufferDesc;
	
	assert(MaxSize <= D3D11_REQ_CONSTANT_BUFFER_ELEMENT_COUNT && (MaxSize % 16) == 0);
	BufferDesc.ByteWidth = MaxSize;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferDesc.MiscFlags = 0;
	
	ConstantBuffers = new LPID3D11Buffer[NumSubBuffers];
	CurrentSubBuffer = 0;
	for(UINT i = 0;i < NumSubBuffers;i++)
	{
		Device->GetDevice()->CreateBuffer(&BufferDesc, NULL, &ConstantBuffers[i]);
		UINT size=BufferDesc.ByteWidth / 2;
		UINT Times=((UINT)(size/16)+1)*16;
		BufferDesc.ByteWidth = Times;
	}
	
	this->Data = new BYTE[MaxSize];
	ZeroMemory(this->Data,MaxSize);
}

BOOL TConstantBuffer::UpdateConstantBufferResource( BOOL isDiscard )
{
	if(HasData)
	{
		if ( isDiscard )
		{
			TotalUpdateSize = CurrentUpdateSize;
		}
		else
		{
			TotalUpdateSize = max( CurrentUpdateSize, TotalUpdateSize );
		}
		
		CurrentSubBuffer = 1;
		UINT BufferSize = MaxSize / 2;
		while ( BufferSize >= TotalUpdateSize && CurrentSubBuffer < NumSubBuffers )
		{
			CurrentSubBuffer++;
			BufferSize /= 2;
		}
		CurrentSubBuffer--;
		BufferSize *= 2;
		ID3D11Buffer* Buffer = ConstantBuffers[CurrentSubBuffer];
		Device->GetDeviceContext()->UpdateSubresource(Buffer,0,NULL,(void*)Data,BufferSize,BufferSize);
		HasData = FALSE;
		CurrentUpdateSize = 0;
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void TConstantBuffer::UpdateBufferData(LPVOID pData, WORD Offset, WORD Size)
{
	HasData = TRUE;
	BYTE* pLocalData=(BYTE*)pData;
	CopyMemory(this->Data+Offset,pLocalData,Size);
	CurrentUpdateSize = max( (UINT)(Offset + Size), CurrentUpdateSize );
}

void TConstantBuffer::PostConstantBuffer(UINT StartSlot,UINT NumBuffers)
{
	ID3D11DeviceContext* DeviceContext=Device->GetDeviceContext();
	DeviceContext->VSSetConstantBuffers(StartSlot,NumBuffers,&ConstantBuffers[CurrentSubBuffer]);
}

ID3D11Buffer* TConstantBuffer::GetConstantBuffer()
{
	return ConstantBuffers[CurrentSubBuffer];
}

void TConstantBuffer::Release()
{
	if(Data)
	{
		SAFE_DELETE_ARRAY(Data);
	}
	if(ConstantBuffers)
	{
		UINT i;
		for(i = 0;i < NumSubBuffers;++i)
		{
			SAFE_RELEASE(ConstantBuffers[i]);
		}
	}
}
