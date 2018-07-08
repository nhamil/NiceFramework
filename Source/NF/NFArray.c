#include "NF/NFArray.h" 

#include "NF/NFMemory.h" 

struct NFArray 
{
    NFbyte *data; 
    NFulong elemSize; 
    NFuint size; 
    NFuint capacity; 
};

static inline NFulong ArrayOffset(NFArrayConstRef arr, NFuint index) 
{
    return arr->elemSize * index; 
}

static NFvoid ReserveArray(NFArrayRef arr, NFuint minSize) 
{
    NFuint cap = arr->capacity; 

    while (cap < minSize) cap *= 2; 

    if (cap != arr->capacity) 
    {
        arr->capacity = cap; 
        arr->data = NFRealloc(arr->data, cap, arr->elemSize); 
    }
}

static NFvoid ResizeArray(NFArrayRef arr, NFuint newSize, NFbool zero) 
{
    if (arr->size == newSize) return; 

    if (arr->size > newSize) 
    {
        arr->size = newSize; 
        return; 
    }

    ReserveArray(arr, newSize); 
    arr->size = newSize; 

    if (zero) NFZeroMemory(arr->data + ArrayOffset(arr, arr->size), ArrayOffset(arr, newSize - arr->size)); 
}

NFArrayRef NFCreateArray(NFulong elemSize, NFuint count, const NFvoid *data) 
{
    NFArrayRef arr = NFNewStruct(1, NFArray); 

    arr->elemSize = elemSize; 
    arr->size = count; 
    arr->capacity = 10; 
    arr->data = NFCalloc(10, elemSize); 

    if (count) NFAppendArray(arr, count, data); 

    return arr; 
} 

NFvoid NFDestroyArray(NFArrayRef arr) 
{
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

NFvoid NFGetArray(NFArrayConstRef arr, NFuint index, NFuint count, NFvoid *data) 
{
    NF_ASSERT(arr); 
    NF_ASSERT(index + count <= arr->size); 
    NF_RETURN_ON_FAIL(count && data); 

    NFCopyMemory(data, arr->data + ArrayOffset(arr, index), ArrayOffset(arr, count)); 
}

NFvoid NFSetArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    NF_ASSERT(arr); 
    NF_ASSERT(index <= arr->size); 
    NF_RETURN_ON_FAIL(count); 
    
    if (arr->size < index + count) ResizeArray(arr, index + count, NF_FALSE); 

    NFCopyMemory(arr->data + ArrayOffset(arr, index), data, ArrayOffset(arr, count)); 
} 

NFvoid NFAppendArray(NFArrayRef arr, NFuint count, const NFvoid *data) 
{
    NFuint oldSize; 

    NF_ASSERT(arr); 
    NF_RETURN_ON_FAIL(count); 

    oldSize = arr->size; 

    ResizeArray(arr, arr->size + count, NF_FALSE); 
    NFCopyMemory(arr->data + ArrayOffset(arr, oldSize), data, ArrayOffset(arr, count)); 
} 

NFvoid NFInsertArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    NF_ASSERT(arr); 
    NF_ASSERT(index <= arr->size); 
    NF_RETURN_ON_FAIL(count); 
    
    ResizeArray(arr, arr->size + count, NF_FALSE); 

    if (index < arr->size) 
    {
        // move values 
        NFMoveMemory(arr->data + ArrayOffset(arr, index + count), arr->data + ArrayOffset(arr, index), ArrayOffset(arr, arr->size - index - count)); 
        NFCopyMemory(arr->data + ArrayOffset(arr, index), data, ArrayOffset(arr, count)); 
    }
    else 
    {
        // append values 
        NFAppendArray(arr, count, data); 
    }
} 

NFvoid NFRemoveArray(NFArrayRef arr, NFuint index, NFuint count) 
{
    NFuint oldSize; 

    NF_ASSERT(arr); 
    NF_ASSERT(index + count <= arr->size); 
    NF_RETURN_ON_FAIL(count); 

    oldSize = arr->size; 
    arr->size -= count; 

    NFMoveMemory(arr->data + ArrayOffset(arr, index), arr->data + ArrayOffset(arr, index + count), ArrayOffset(arr, count)); 
} 
