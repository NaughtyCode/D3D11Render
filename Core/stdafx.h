#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN

#include <tbb/scalable_allocator.h>

#pragma comment(lib, "psapi.lib")

#if defined(_DEBUG) || defined(DEBUG)
    #pragma comment(lib, "tbb_debug.lib")
    #pragma comment(lib, "tbbproxy_debug.lib")
    #pragma comment(lib, "tbbmalloc_debug.lib")
    #pragma comment(lib, "tbb_preview_debug.lib")
    #pragma comment(lib, "tbbmalloc_proxy_debug.lib")
    
#else
    #pragma comment(lib, "tbb.lib")
    #pragma comment(lib, "tbbproxy.lib")
    #pragma comment(lib, "tbbmalloc.lib")
    #pragma comment(lib, "tbb_preview.lib")
    #pragma comment(lib, "tbbmalloc_proxy.lib")
#endif


// Windows head fiels
#include <windows.h>
#include <commctrl.h>
#include <basetsd.h>
#include <crtdbg.h>


// C head fiels
#include <cassert>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <cfloat>
#include <cmath>
#include <cstdlib>

#include <malloc.h>
#include <memory.h>
#include <tchar.h>




// C++ head fiels
#include <map>
#include <string>
#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <sstream>



// Direct3D 11 head fiels
#include <d3d11.h>
#include <D3Dcompiler.h>
#include <D3DX11async.h>
#include <xnamath.h>

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)            { if (p) { delete (p);     (p)=NULL; } }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)      { if (p) { delete[] (p);   (p)=NULL; } }
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)           { if (p) { (p)->Release(); (p)=NULL; } }
#endif

#ifndef SAFE_RELEASEDELETE
#define SAFE_RELEASEDELETE(p)     { if (p) { (p)->Release(); delete p;(p)=NULL; } }
#endif

#ifndef FORCEINLINE
#define FORCEINLINE inline
#endif

typedef ID3D11Buffer* LPID3D11Buffer;


#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>


// tinyxml head files
#include "tinyxml.h"


#ifndef MAXFILENAME
#define MAXFILENAME          1024
#endif


#ifndef MAXSHADERPROFILE
#define MAXSHADERPROFILE     128
#endif


#ifndef MAXSHADERENTRY
#define MAXSHADERENTRY       256
#endif


#ifndef CONFIG_MAX_LINE
#define CONFIG_MAX_LINE      2048
#endif

#ifndef CONFIG_MAX_SECTION
#define CONFIG_MAX_SECTION   1024
#endif

#ifndef CONFIG_MAX_NAME
#define CONFIG_MAX_NAME      1024
#endif



//shader definitions

#ifndef SHADER_ENTRY_MAX
#define SHADER_ENTRY_MAX 64
#endif


#ifndef SHADER_PROFILE_MAX
#define SHADER_PROFILE_MAX 32
#endif


#ifndef SHADER_FILENAME_MAX
#define SHADER_FILENAME_MAX 512
#endif


#include "Core.h"








