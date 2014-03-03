#include "stdafx.h"
#include "TCamera.h"
#include "TMatrix.h"

TCamera::TCamera(UINT w,UINT h):
			World(XMMatrixIdentity()),
			Width(w),
			Height(h),
			FovAngleY(XM_PIDIV4),
			NearZ(0.01f),
			FarZ(100.0f)
{
	EyeVector = XMVectorSet( 0.0f, 3.0f, -6.0f, 0.0f );
	AtVector = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	UpVector = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	SetProjection();
	SetView();
}

TCamera::~TCamera()
{

}

void TCamera::SetView()
{
	View=XMMatrixLookAtLH( EyeVector, AtVector, UpVector );
}

void TCamera::SetProjection()
{
	Projection = XMMatrixPerspectiveFovLH( XM_PIDIV4,(FLOAT)Width/(FLOAT)Height,NearZ,FarZ);
}

XMMATRIX TCamera::GetTransposeView()
{
	return XMMatrixTranspose(View);
}

XMMATRIX TCamera::GetTransposeWorld()
{
	return XMMatrixTranspose(World);
}

XMMATRIX TCamera::GetTransposeProjection()
{
	return XMMatrixTranspose(Projection);
}

XMMATRIX TCamera::RotationY(FLOAT Angle)
{
	XMMATRIX scale = XMMatrixScaling(0.6f,0.6f,0.6f);
	XMMATRIX rotate = XMMatrixRotationY(Angle);
	XMMATRIX world = scale*rotate;
	return world;
}




