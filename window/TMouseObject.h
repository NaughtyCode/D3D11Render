#ifndef TMOUSEOBJECT_H
#define TMOUSEOBJECT_H

#if _MSC_VER > 1000
# pragma once
#endif

typedef struct MouseStateObject
{
	LONG X;
	LONG Y;
	BYTE Buttons[3];
	BYTE Padding;
}MouseStateObject;


class TMouseObject
{
public:
    TMouseObject(HWND hWnd);
    virtual ~TMouseObject();
    int CreateDirectInput();
    int UpdateInputState();
    VOID Release();
    
private:
    LPDIRECTINPUTDEVICE8   Mouse;
    HWND                   WindowHandle; 
    LPDIRECTINPUT8         DirectInput;
    UINT                   X;
    UINT                   Y;
    
};



#endif


