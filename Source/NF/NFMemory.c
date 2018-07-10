#include "NF/NFMemory.h" 

#include "NF/NFError.h" 

#include <stdlib.h> 
#include <string.h> 

NFvoid NFZeroMemory(NFvoid* mem, NFulong size) 
{
    memset(mem, 0, size); 
}

NFvoid NFCopyMemory(NFvoid *to, const NFvoid *from, NFulong size) 
{
    if (from) 
    {
        memcpy(to, from, size); 
    }
    else 
    {
        memset(to, 0, size); 
    }
}

NFvoid NFMoveMemory(NFvoid *to, const NFvoid *from, NFulong size) 
{
    memmove(to, from, size); 
}

NFint NFCompareMemory(const NFvoid *a, const NFvoid *b, NFulong size) 
{
    return memcmp(a, b, size); 
}

NFvoid *NFMalloc(NFulong num, NFulong size) 
{
    NFvoid *mem = malloc(num * size); 

    if (mem) 
    {
        return mem; 
    }
    else 
    {
        NFFatalError(NF_OUT_OF_MEMORY); 
        return NULL; 
    }
}

NFvoid* NFCalloc(NFulong num, NFulong size) 
{
    NFvoid *newMem = calloc(num, size); 

    if (newMem) 
    {
        return newMem; 
    }
    else 
    {
        NFFatalError(NF_OUT_OF_MEMORY); 
        return NULL; 
    }
} 

NFvoid* NFRealloc(NFvoid* mem, NFulong num, NFulong size) 
{
    NFvoid *newMem = realloc(mem, num * size); 

    if (newMem) 
    {
        return newMem; 
    }
    else 
    {
        NFFatalError(NF_OUT_OF_MEMORY); 
        return NULL; 
    }
}

NFvoid NFFree(NFvoid *mem) 
{
    if (mem) free(mem); 
}
