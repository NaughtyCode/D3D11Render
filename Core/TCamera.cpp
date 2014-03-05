#include "stdafx.h"
#include "TCamera.h"
#include "TMatrix.h"



TBaseCamera::TBaseCamera( ) :
			LookPosition(XMFLOAT3( 0.0f, 0.0f, 0.0f ) ),
			LookTarget( XMFLOAT3( 0.0f, 0.0f, 0.0f ) ),
			Up( XMFLOAT3( 0.0f, 1.0f, 0.0f ) )
{
	
}

TBaseCamera::TBaseCamera( XMFLOAT3 position, XMFLOAT3 target ):
			LookPosition(position),
			LookTarget(target),
			Up(XMFLOAT3(0.0f,1.0f,0.0f))
{
	
}

void TBaseCamera::SetPositions( XMFLOAT3 pos, XMFLOAT3 target )
{
	LookPosition = pos;
	LookTarget = target;
}

XMMATRIX TBaseCamera::GetViewMatrix( )
{
	XMMATRIX view = XMMatrixLookAtLH(
				XMLoadFloat3(&LookPosition),
				XMLoadFloat3(&LookTarget),
				XMLoadFloat3(&Up)
				);
	
	return view;
}

TCamera::TCamera(HWND hWnd):
				WindowHandle(hWnd)
{
	this->InitializeCamera();
}

TCamera::~TCamera()
{
	
}

void TCamera::InitializeCamera()
{
	RECT rc;
	GetClientRect(WindowHandle,&rc);
	Width = rc.right - rc.left;
	Height = rc.bottom - rc.top;

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

XMMATRIX TCamera::GetWorldViewProMatrix()
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

void TCamera::Release()
{

}