#pragma once 

#ifndef NFMEMORY_H 
#define NFMEMORY_H 

#include "NF/NFCommon.h" 

#define NFNewStruct(count, type) NFCalloc(count, sizeof (struct type))

NF_EXTERN_C_BEGIN 

NFvoid NFZeroMemory(NFvoid *mem, NFulong size); 

NFvoid NFCopyMemory(NFvoid *to, const NFvoid *from, NFulong size); 

NFvoid *NFMalloc(NFulong num, NFulong size); 

NFvoid *NFCalloc(NFulong num, NFulong size); 

NFvoid *NFRealloc(NFvoid *mem, NFulong num, NFulong size); 

NFvoid NFFree(NFvoid *mem); 

NF_EXTERN_C_FINISH 

#endif