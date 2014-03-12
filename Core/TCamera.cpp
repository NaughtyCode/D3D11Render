#include "stdafx.h"
#include "TCamera.h"

TCamera::TCamera(HWND hWnd):WindowHandle(hWnd)
{
	RECT rc;
	GetClientRect(WindowHandle,&rc);
	UINT Width = rc.right - rc.left;
	UINT Height = rc.bottom - rc.top;
	XMMATRIX world,view,proj,rotate,production;
	XMVECTOR Eye,LookAt,LookUp;
	
	Eye = XMVectorSet( 0.0f, 3.0f, -12.0f, 0.0f );
	LookAt = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	LookUp = XMVectorSet( 0.0f, 1.0f, 0.0f, 0.0f );
	
	world = XMMatrixIdentity();
	view=XMMatrixLookAtLH( Eye, LookAt, LookUp );
	proj = XMMatrixPerspectiveFovLH( XM_PIDIV4,(FLOAT)Width/(FLOAT)Height,0.01f,100.0f);
	rotate = XMMatrixRotationY(0.3f);
	world=XMMatrixTranspose(world);
	view=XMMatrixTranspose(view);
	proj=XMMatrixTranspose(proj);
	production = (proj*view)*world;
	
	GMVP.Identity();
	
	memcpy(&GMVP.m[0][0],&production.m[0][0],sizeof(FLOAT)*16);
}

TMatrix TCamera::GetWorldViewProMatrix()
{
	return GMVP;
}
