#include "NF/NFMemory.h" 

#include <stdlib.h> 
#include <string.h> 

NFvoid NFZeroMemory(NFvoid* mem, NFulong size) 
{
    memset(mem, 0, size); 
}

NFvoid NFCopyMemory(NFvoid *to, const NFvoid *from, NFulong size) 
{
    memcpy(to, from, size); 
}

NFvoid *NFMalloc(NFulong num, NFulong size) 
{
    return malloc(num * size); 
}

NFvoid* NFCalloc(NFulong num, NFulong size) 
{
    return calloc(num, size); 
} 

NFvoid* NFRealloc(NFvoid* mem, NFulong num, NFulong size) 
{
    return realloc(mem, num * size); 
}

NFvoid NFFree(NFvoid *mem) 
{
    free(mem); 
}