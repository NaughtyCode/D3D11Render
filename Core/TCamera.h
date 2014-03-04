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
	void InitializeCamera();
	XMMATRIX GetMatrix();
    XMMATRIX RotationY(FLOAT Angle);
    
private:
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

