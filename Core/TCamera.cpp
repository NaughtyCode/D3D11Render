#include "stdafx.h"
#include "TCamera.h"

TCamera::TCamera():mPosition(0.0f, 3.0f, -12.0f), 
	mRight(1.0f, 0.0f, 0.0f),
	mUp(0.0f, 1.0f, 0.0f),
	mLook(0.0f, 1.0f,0.0f)
{
	SetLens(XM_PIDIV4, 1.0f, 1.0f, 1000.0f);
}

TCamera::~TCamera()
{
	
}

XMVECTOR TCamera::GetPositionXM()const
{
	return XMLoadFloat3(&mPosition);
}

XMFLOAT3 TCamera::GetPosition()const
{
	return mPosition;
}

void TCamera::SetPosition(float x, float y, float z)
{
	mPosition = XMFLOAT3(x, y, z);
}

void TCamera::SetPosition(const XMFLOAT3& v)
{
	mPosition = v;
}

XMVECTOR TCamera::GetRightXM()const
{
	return XMLoadFloat3(&mRight);
}

XMFLOAT3 TCamera::GetRight()const
{
	return mRight;
}

XMVECTOR TCamera::GetUpXM()const
{
	return XMLoadFloat3(&mUp);
}

XMFLOAT3 TCamera::GetUp()const
{
	return mUp;
}

XMVECTOR TCamera::GetLookXM()const
{
	return XMLoadFloat3(&mLook);
}

XMFLOAT3 TCamera::GetLook()const
{
	return mLook;
}

float TCamera::GetNearZ()const
{
	return mNearZ;
}

float TCamera::GetFarZ()const
{
	return mFarZ;
}

float TCamera::GetAspect()const
{
	return mAspect;
}

float TCamera::GetFovY()const
{
	return mFovY;
}

float TCamera::GetFovX()const
{
	float halfWidth = 0.5f*GetNearWindowWidth();
	return 2.0f*atan(halfWidth / mNearZ);
}

float TCamera::GetNearWindowWidth()const
{
	return mAspect * mNearWindowHeight;
}

float TCamera::GetNearWindowHeight()const
{
	return mNearWindowHeight;
}

float TCamera::GetFarWindowWidth()const
{
	return mAspect * mFarWindowHeight;
}

float TCamera::GetFarWindowHeight()const
{
	return mFarWindowHeight;
}

void TCamera::SetLens(float fovY, float aspect, float zn, float zf)
{
	mFovY = fovY;
	mAspect = aspect;
	mNearZ = zn;
	mFarZ = zf;

	mNearWindowHeight = 2.0f * mNearZ * tanf( 0.5f*mFovY );
	mFarWindowHeight  = 2.0f * mFarZ * tanf( 0.5f*mFovY );

	XMMATRIX P = XMMatrixPerspectiveFovLH(mFovY, mAspect, mNearZ, mFarZ);
	XMStoreFloat4x4(&mProj, P);
}

void TCamera::LookAt(FXMVECTOR pos, FXMVECTOR target, FXMVECTOR worldUp)
{
	XMVECTOR L = XMVector3Normalize(XMVectorSubtract(target, pos));
	XMVECTOR R = XMVector3Normalize(XMVector3Cross(worldUp, L));
	XMVECTOR U = XMVector3Cross(L, R);

	XMStoreFloat3(&mPosition, pos);
	XMStoreFloat3(&mLook, L);
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
}

void TCamera::LookAt(const XMFLOAT3& pos, const XMFLOAT3& target, const XMFLOAT3& up)
{
	XMVECTOR P = XMLoadFloat3(&pos);
	XMVECTOR T = XMLoadFloat3(&target);
	XMVECTOR U = XMLoadFloat3(&up);

	LookAt(P, T, U);
}

XMMATRIX TCamera::View()const
{
	return XMLoadFloat4x4(&mView);
}

XMMATRIX TCamera::Proj()const
{
	return XMLoadFloat4x4(&mProj);
}

XMMATRIX TCamera::ViewProj()const
{
	return XMMatrixMultiply(View(), Proj());
}

XMMATRIX TCamera::GetWorldViewProMatrix()const
{
	XMMATRIX world,view,proj;
	
	XMVECTOR Eye = XMVectorSet( mPosition.x,mPosition.y,mPosition.z, 0.0f );
	XMVECTOR LookAt = XMVectorSet(mLook.x,mLook.y,mLook.z, 0.0f );
	XMVECTOR Up = XMVectorSet( mUp.x,mUp.y,mUp.z, 0.0f );
	
	world = XMMatrixIdentity();
	view=XMMatrixLookAtLH( Eye, LookAt, Up );
	proj = XMMatrixPerspectiveFovLH( XM_PIDIV4,mAspect,mNearZ,mFarZ);
	
	world=XMMatrixTranspose(world);
	view=XMMatrixTranspose(view);
	proj=XMMatrixTranspose(proj);
	
	return proj*view*world;
}

void TCamera::Strafe(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR r = XMLoadFloat3(&mRight);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, r, p));
}

void TCamera::Walk(float d)
{
	XMVECTOR s = XMVectorReplicate(d);
	XMVECTOR l = XMLoadFloat3(&mLook);
	XMVECTOR p = XMLoadFloat3(&mPosition);
	XMStoreFloat3(&mPosition, XMVectorMultiplyAdd(s, l, p));
}

void TCamera::Pitch(float angle)
{
	XMMATRIX R = XMMatrixRotationAxis(XMLoadFloat3(&mRight), angle);

	XMStoreFloat3(&mUp,   XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void TCamera::RotateY(float angle)
{
	XMMATRIX R = XMMatrixRotationY(angle);
	XMStoreFloat3(&mRight,   XMVector3TransformNormal(XMLoadFloat3(&mRight), R));
	XMStoreFloat3(&mUp, XMVector3TransformNormal(XMLoadFloat3(&mUp), R));
	XMStoreFloat3(&mLook, XMVector3TransformNormal(XMLoadFloat3(&mLook), R));
}

void TCamera::UpdateViewMatrix()
{
	XMVECTOR R = XMLoadFloat3(&mRight);
	XMVECTOR U = XMLoadFloat3(&mUp);
	XMVECTOR L = XMLoadFloat3(&mLook);
	XMVECTOR P = XMLoadFloat3(&mPosition);
	
	L = XMVector3Normalize(L);
	U = XMVector3Normalize(XMVector3Cross(L, R));
	R = XMVector3Cross(U, L);
	
	float x = -XMVectorGetX(XMVector3Dot(P, R));
	float y = -XMVectorGetX(XMVector3Dot(P, U));
	float z = -XMVectorGetX(XMVector3Dot(P, L));
	
	XMStoreFloat3(&mRight, R);
	XMStoreFloat3(&mUp, U);
	XMStoreFloat3(&mLook, L);
	
	mView(0,0) = mRight.x; mView(0,1) = mUp.x; mView(0,2) = mLook.x; mView(0,3) = 0.0f;
	mView(1,0) = mRight.y; mView(1,1) = mUp.y; mView(1,2) = mLook.y; mView(1,3) = 0.0f;
	mView(2,0) = mRight.z; mView(2,1) = mUp.z; mView(2,2) = mLook.z; mView(2,3) = 0.0f;
	mView(3,0) = x;        mView(3,1) = y;     mView(3,2) = z;       mView(3,3) = 1.0f;
}

void TCamera::Release()
{
    
}