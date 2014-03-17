#ifndef TMALLOC_H
#define TMALLOC_H

#if _MSC_VER > 1000
# pragma once
#endif

#define DEFAULT_ALIGNMENT 8

class TMalloc
{
public:
    TMalloc(){}
    ~TMalloc(){}
    virtual void* Malloc(DWORD Size, DWORD Alignment) = 0;
    virtual void* Realloc(void* Ptr, DWORD NewSize, DWORD Alignment) = 0;
    virtual void Free(void* Ptr) = 0;
};

#endif
