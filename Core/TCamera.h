#ifndef TCAMERA_H
#define TCAMERA_H

#if _MSC_VER > 1000
# pragma once
#endif

class TCamera
{
public:
    TCamera(UINT w,UINT h);
    ~TCamera();
    void SetView();
    void SetProjection();
    XMMATRIX GetTransposeView();
    XMMATRIX GetTransposeWorld();
    XMMATRIX GetTransposeProjection();
	XMMATRIX GetMatrix();
    XMMATRIX RotationY(FLOAT Angle);
    
private:
    XMMATRIX World;
    XMMATRIX View;
    XMMATRIX Projection;
    XMVECTOR EyeVector;
    XMVECTOR AtVector;
    XMVECTOR UpVector;
    UINT     Width;
    UINT     Height;
    FLOAT    FovAngleY;
    FLOAT    AspectRatio;
    FLOAT    NearZ;
    FLOAT    FarZ;
	FLOAT    Speed;

};



#endif

