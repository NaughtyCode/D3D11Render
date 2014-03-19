#ifndef INICONFIG_H
#define INICONFIG_H


#if _MSC_VER > 1000
# pragma once
#endif

#include "TResource.h"

class TRenderContents;


typedef int (*ProcessCallBackType)(void* user,
        const char* SectionName,
        const char* ItemName,
        const char* Data);

INT ParseResourceFile(const char* FileName,
                    ProcessCallBackType CallBack,
                    void* user);

INT LoadRenderContentHandler(TRenderContents* Object,
        const char* SectionName,
        const char* ItemName,
        char* Data);

#endif
