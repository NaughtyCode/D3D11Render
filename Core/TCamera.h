#pragma once

class TCamera
{
public:
	TCamera(UINT w,UINT h);
	~TCamera();
	void SetView();
	void SetProjection();
	XMMATRIX GetTransposeView();
	XMMATRIX GetTransposeProjection();
	XMMATRIX GetTransposeWorld();
	
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
};



