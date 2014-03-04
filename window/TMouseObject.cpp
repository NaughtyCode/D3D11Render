#include "stdafx.h"
#include "TMouseObject.h"


static DIOBJECTDATAFORMAT GObjectFormats[] =
{
    { &GUID_XAxis, FIELD_OFFSET( MouseStateObject, X ),     DIDFT_AXIS   | DIDFT_ANYINSTANCE,                  0 },
    { &GUID_YAxis, FIELD_OFFSET( MouseStateObject, Y ),     DIDFT_AXIS   | DIDFT_ANYINSTANCE,                  0 },
    { 0,           FIELD_OFFSET( MouseStateObject, Buttons[0] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE,                  0 },
    { 0,           FIELD_OFFSET( MouseStateObject, Buttons[1] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 },
    { 0,           FIELD_OFFSET( MouseStateObject, Buttons[2] ), DIDFT_BUTTON | DIDFT_ANYINSTANCE | DIDFT_OPTIONAL, 0 }
};


static DIDATAFORMAT GMouse =
{
    sizeof( DIDATAFORMAT ),
    sizeof( DIOBJECTDATAFORMAT ),
    DIDF_ABSAXIS,
    sizeof( MouseStateObject ),
    (sizeof(GObjectFormats) / sizeof(DIOBJECTDATAFORMAT)),
    GObjectFormats
};


TMouseObject::TMouseObject(HWND hWnd):
                Mouse(0),
                WindowHandle(hWnd),
                DirectInput(0)
{

}

TMouseObject::~TMouseObject()
{
    
}

int TMouseObject::CreateDirectInput()
{
    HRESULT hr;
    hr = DirectInput8Create(
                    GetModuleHandle(NULL),
                    DIRECTINPUT_VERSION,
                    IID_IDirectInput8,
                    (VOID**)&DirectInput,
                    NULL );
    
    if( FAILED(hr) )
    {
        return 0;
    }
    
    hr = DirectInput->CreateDevice(
                    GUID_SysMouse,
                    &Mouse,
                    NULL);
    
    if( FAILED(hr) )
    {
        return 0;
    }
    
    hr = Mouse->SetDataFormat(&GMouse);
    
    if( FAILED(hr) )
    {
        return 0;
    }
    
    hr = Mouse->SetCooperativeLevel(
                        WindowHandle,
                        DISCL_NONEXCLUSIVE|DISCL_FOREGROUND);
    
    if( FAILED(hr) )
    {
        return 0;
    }
    
    return 1;
}

int TMouseObject::UpdateInputState()
{
    HRESULT hr;
    
    MouseStateObject StateObject;
    static POINT point = {0};
    static BOOL bInitialized = FALSE;
    
    if( NULL==Mouse )
    {
        return 0;
    }
    
    hr = Mouse->Poll();
    if( FAILED( hr ) )
    {
        hr = Mouse->Acquire();
        while( hr == DIERR_INPUTLOST )
            hr = Mouse->Acquire();
        return 0;
    }
    
    hr = Mouse->GetDeviceState(sizeof(MouseStateObject),&StateObject);
    
    if( FAILED(hr) )
    {
        return 0;
    }
    
    if( !bInitialized )
    {
        bInitialized = TRUE;
        point.x = StateObject.X;
        point.y = StateObject.Y;
    }
    
    X = StateObject.X - point.x;
    Y = StateObject.Y - point.y;
    
    printf("(%d,%d)\n",X,Y);
    
    for( int i = 0; i < 3; i++ )
    {
        if( StateObject.Buttons[i] & 0x80 )
        {
            
        }
    }
    
    return 1;
}

VOID TMouseObject::Release()
{
    if( Mouse )
    {
        Mouse->Unacquire();
    }
    
    SAFE_RELEASE(Mouse);
    SAFE_RELEASE(DirectInput);
}
