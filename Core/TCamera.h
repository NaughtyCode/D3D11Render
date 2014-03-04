#ifndef TCAMERA_H
#define TCAMERA_H

#if _MSC_VER > 1000
# pragma once
#endif

class TBaseCamera
{
public:
    TBaseCamera();
    TBaseCamera(XMFLOAT3 pos, XMFLOAT3 target);
    void SetPositions( XMFLOAT3 pos, XMFLOAT3 target);
    XMMATRIX GetViewMatrix();
    void Release();

private:
    XMFLOAT3 LookPosition;
    XMFLOAT3 LookTarget;
    XMFLOAT3 Up;
};

class TCamera
{
public:
    TCamera(HWND hWnd);
    ~TCamera();
    void InitializeCamera();
    XMMATRIX GetMatrix();
    XMMATRIX RotationY(FLOAT Angle);
	void Release();

private:
	HWND     WindowHandle;
    XMMATRIX World,View,Projection;
    XMVECTOR Eye,LookAt,LookUp;
    UINT     Width,Height;
    FLOAT    FovAngleY;
    FLOAT    AspectRatio;
    FLOAT    NearZ;
    FLOAT    FarZ;
    FLOAT    Speed;

};



#endif

