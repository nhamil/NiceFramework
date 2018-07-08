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
    if (!arr || !arr->data || index + count > arr->size) 
    {
        NFZeroMemory(data, count * arr->elemSize); 
        return NF_FALSE; 
    }

    if (count) 
    {
        NFCopyMemory(data, arr->data + ArrayOffset(arr, index), ArrayOffset(arr, count)); 
    }

    return NF_TRUE; 
}

NFbool NFSetArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    NF_RETURN_VAL_ON_FAIL(arr && arr->data && count && index <= arr->size, NF_FALSE); 

    if (arr->size < index + count) ResizeArray(arr, index + count, NF_FALSE); 

    NFCopyMemory(arr->data + ArrayOffset(arr, index), data, ArrayOffset(arr, count)); 

    return NF_TRUE; 
} 

NFbool NFAppendArray(NFArrayRef arr, NFuint count, const NFvoid *data) 
{
    NFuint oldSize; 

    NF_RETURN_VAL_ON_FAIL(arr && count, NF_FALSE); 

    oldSize = arr->size; 

    ResizeArray(arr, arr->size + count, NF_FALSE); 
    NF_RETURN_VAL_ON_FAIL(arr->data, NF_FALSE); 

    NFCopyMemory(arr->data + ArrayOffset(arr, oldSize), data, ArrayOffset(arr, count)); 

    return NF_TRUE; 
} 

NFbool NFInsertArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    NF_RETURN_VAL_ON_FAIL(arr && arr->data && count && index <= arr->size, NF_FALSE); 

    ResizeArray(arr, arr->size + count, NF_FALSE); 
    NF_RETURN_VAL_ON_FAIL(arr->data, NF_FALSE); 

    if (index < arr->size) 
    {
        // move values 
        NFMoveMemory(arr->data + ArrayOffset(arr, index + count), arr->data + ArrayOffset(arr, index), ArrayOffset(arr, arr->size - index - count)); 
        NFCopyMemory(arr->data + ArrayOffset(arr, index), data, ArrayOffset(arr, count)); 

        return NF_TRUE; 
    }
    else 
    {
        // append values 
        return NFAppendArray(arr, count, data); 
    }
} 

NFbool NFRemoveArray(NFArrayRef arr, NFuint index, NFuint count) 
{
    NFuint oldSize; 

    NF_RETURN_VAL_ON_FAIL(arr && arr->data && count && index + count <= arr->size, NF_FALSE); 

    oldSize = arr->size; 
    arr->size -= count; 

    NFMoveMemory(arr->data + ArrayOffset(arr, index), arr->data + ArrayOffset(arr, index + count), ArrayOffset(arr, count)); 

    return NF_TRUE; 
} 
