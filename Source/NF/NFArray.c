#include "NF/NFArray.h" 

#include "NF/NFMemory.h" 

struct NFArray 
{
    NFbyte *data; 
    NFulong elemSize; 
    NFuint size; 
    NFuint capacity; 
};

static NFulong ArrayOffset(NFArrayConstRef arr, NFuint index) 
{
    return arr->elemSize * index; 
}

static NFvoid ResizeArray(NFArrayRef arr, NFuint newSize, NFbool zero) 
{
    if (arr->size == newSize) return; 

    if (arr->size > newSize) 
    {
        arr->size = newSize; 

        // TODO 
        // if (zero) NFZeroMemory(arr->data + ArrayOffset())
    }

    NFuint cap = arr->capacity; 

    while (cap < newSize) cap *= 2; 

    arr->capacity = cap; 
    arr->data = NFRealloc(arr->data, cap, arr->elemSize); 

    if (zero) 
    {
        NFZeroMemory(arr->data + ArrayOffset(arr, arr->size), ArrayOffset(arr, newSize - arr->size)) 
    }
}

NFArrayRef NFCreateArray(NFulong elemSize, NFuint count, const NFvoid *data) 
{
    NFArrayRef arr = NFNewStruct(1, NFArray); 

    NF_RETURN_VAL_ON_FAIL(arr, NULL); 

    arr->elemSize = elemSize; 
    arr->size = count; 
    arr->capacity = 10; 
    arr->data = NFCalloc(10, elemSize); 

    if (count) NFAppendArray(arr, count, data); 

    return arr; 
} 

NFvoid NFDestroyArray(NFArrayRef arr) 
{
    NF_RETURN_ON_FAIL(arr); 

    NFFree(arr->data); 
    NFFree(arr); 
} 

NFuint NFArraySize(NFArrayConstRef arr) 
{
    return arr ? arr->size : 0U; 
}

NFulong NFArrayElemSize(NFArrayConstRef arr) 
{
    return arr ? arr->elemSize : 0ULL; 
}

NFbool NFGetArray(NFArrayConstRef arr, NFuint index, NFuint count, NFvoid *data) 
{
    NF_RETURN_VAL_ON_FAIL(arr, NF_FALSE); 
    NF_RETURN_VAL_ON_FAIL(data, NF_FALSE); 
    NF_RETURN_VAL_ON_FAIL(index + count < arr->size, NF_FALSE); 

    if (count) 
    {
        NFCopyMemory(data, arr->data + ArrayOffset(arr, index), ArrayOffset(arr, count)); 
    }
    else 
    {
        NFZeroMemory(data, ArrayOffset(arr, count)); 
    }

    return NF_TRUE; 
}

NFvoid NFSetArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    // TODO 
} 

NFvoid NFAppendArray(NFArrayRef arr, NFuint count, const NFvoid *data) 
{
    // TODO 
} 

NFvoid NFInsertArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    // TODO 
} 

NFvoid NFRemoveArray(NFArrayRef arr, NFuint index, NFuint count) 
{
    // TODO 
} 
