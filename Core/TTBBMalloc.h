#ifndef TTBBMALLOC_H
#define TTBBMALLOC_H

#if _MSC_VER > 1000
# pragma once
#endif

#include "stdafx.h"
#include "TMalloc.h"

#pragma pack(push,8) 
#include <Psapi.h>
#pragma pack(pop)




class TTBBMalloc : public TMalloc
{
public:
	TTBBMalloc ()
	{
	}
	
	~TTBBMalloc ()
	{
	}
	
public:
	void OutputMemoryError() const
	{
		printf("Memory is not enough\n");
	}
	
	virtual void* Malloc (DWORD Size, DWORD Alignment)
	{
		assert(Alignment==MALLOCALIGNMENT);
		void* NewPtr = scalable_malloc(Size);
		if (NewPtr == NULL)
		{
			OutputMemoryError();
		}
		UsedCurrent += scalable_msize(NewPtr);
		UsedPeak = max(UsedPeak, UsedCurrent);
		CurrentAllocs++;
		TotalAllocs++;
		return NewPtr;
	}
	
	virtual void* Realloc (void* Ptr, DWORD NewSize, DWORD Alignment)
	{
		assert(Alignment==MALLOCALIGNMENT);
		void* NewPtr = NULL;
		
		if (NewSize == 0)
		{
			Free(Ptr);
		}
		else if (Ptr == NULL)
		{
			NewPtr = Malloc(NewSize, Alignment);
		}
		else
		{
			DWORD OldSize = scalable_msize(Ptr);
			NewPtr = scalable_realloc(Ptr, NewSize);
			assert(UsedCurrent >= OldSize);
			UsedCurrent -= OldSize;
			UsedCurrent += (NewPtr != NULL) ? scalable_msize(NewPtr) : 0;
			UsedPeak = max(UsedPeak, UsedCurrent);
		}
		return NewPtr;
	}
	
	virtual void Free (void* Ptr)
	{
		if (Ptr == NULL)
		{
			return;
		}
		
		DWORD OldSize = scalable_msize(Ptr);
		
		scalable_free(Ptr);
		
		assert(UsedCurrent >= OldSize);
		assert(CurrentAllocs > 0);
		
		UsedCurrent -= OldSize;
		CurrentAllocs--;
	}
	
	SIZE_T GetOSAvailableMemory () const
	{
		PROCESS_MEMORY_COUNTERS MemCounters;
		GetProcessMemoryInfo(GetCurrentProcess(), &MemCounters, sizeof(MemCounters));
		return MemCounters.WorkingSetSize;
	}
	
	SIZE_T GetOSUsedMemory () const
	{
		PERFORMANCE_INFORMATION PerfInfo;
		GetPerformanceInfo(&PerfInfo, sizeof(PerfInfo));
		return PerfInfo.PhysicalAvailable;
	}
	
private:
	DWORD CurrentAllocs;
	DWORD TotalAllocs;
	DWORD UsedCurrent;
	DWORD UsedPeak;
};

#endif
