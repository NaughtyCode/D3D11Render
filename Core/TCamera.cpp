#include "stdafx.h"
#include "TCamera.h"
#include "TMatrix.h"

TCamera::TCamera(UINT w,UINT h):
			Width(w),
			Height(h)
{
	this->InitializeCamera();
}

TCamera::~TCamera()
{
	
}

void TCamera::InitializeCamera()
{
	World = XMMatrixIdentity();
	Eye = XMVectorSet( 0.0f, 3.0f, -12.0f, 0.0f );
	LookAt  = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	LookUp  = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	FovAngleY = XM_PIDIV4;
	NearZ = 0.01f;
	FarZ = 100.0f;
	View=XMMatrixLookAtLH( Eye, LookAt, LookUp );
	Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4,(FLOAT)Width/(FLOAT)Height,NearZ,FarZ);
}

XMMATRIX TCamera::RotationY(FLOAT Angle)
{
	XMMATRIX m = XMMatrixRotationY(Angle);
	return m;
}

XMMATRIX TCamera::GetMatrix()
{
	XMMATRIX world,
		view,
		projection;
	XMMATRIX rotate;
	rotate = this->RotationY(0.3);
	world=XMMatrixTranspose(World);
	view=XMMatrixTranspose(View);
	projection=XMMatrixTranspose(Projection);
	XMMATRIX result;
	result = (projection*view)*world;
	return result*rotate;
}

