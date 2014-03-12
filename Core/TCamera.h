#ifndef TCAMERA_H
#define TCAMERA_H

#if _MSC_VER > 1000
# pragma once
#endif





class TCamera
{
public:
    TCamera(HWND hWnd);
    ~TCamera(){}
    void Release(){}
    TMatrix GetWorldViewProMatrix();
    
private:
    HWND  WindowHandle;
    TMatrix  GMVP;
};




#endif

