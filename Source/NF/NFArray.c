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

static NFvoid ArrayReserve(NFArrayRef arr, NFuint minSize) 
{
    NFuint cap = arr->capacity; 

    while (cap < minSize) cap *= 2; 

    if (cap != arr->capacity) 
    {
        arr->capacity = cap; 
        arr->data = NFRealloc(arr->data, cap, arr->elemSize); 
    }
}

static NFvoid ArrayResize(NFArrayRef arr, NFuint newSize, NFbool zero) 
{
    if (arr->size == newSize) return; 

    if (arr->size > newSize) 
    {
        arr->size = newSize; 
        return; 
    }

    ArrayReserve(arr, newSize); 
    arr->size = newSize; 

    if (zero) NFZeroMemory(arr->data + ArrayOffset(arr, arr->size), ArrayOffset(arr, newSize - arr->size)); 
}

NFArrayRef NFArrayCreate(NFulong elemSize, NFuint count, const NFvoid *data) 
{
    NFArrayRef arr = NFNewStruct(1, NFArray); 

    arr->elemSize = elemSize; 
    arr->size = count; 
    arr->capacity = 10; 
    arr->data = NFCalloc(10, elemSize); 

    if (count) NFArrayAppendRange(arr, count, data); 

    return arr; 
} 

NFvoid NFArrayDestroy(NFArrayRef arr) 
{
    NFFree(arr->data); 
    NFFree(arr); 
} 

NFuint NFArraySize(NFArrayConstRef arr) 
{
    NF_ASSERT_VAL(arr, 0U); 

    return arr->size; 
}

NFulong NFArrayElemSize(NFArrayConstRef arr) 
{
    NF_ASSERT_VAL(arr, 0ULL); 

    return arr->elemSize; 
}

NFvoid NFArrayGetRange(NFArrayConstRef arr, NFuint index, NFuint count, NFvoid *data) 
{
    NF_ASSERT(arr); 
    NF_ASSERT(index + count <= arr->size); 
    NF_RETURN_ON_FAIL(count && data); 

    NFCopyMemory(data, arr->data + ArrayOffset(arr, index), ArrayOffset(arr, count)); 
}

NFvoid *NFArrayGetRef(NFArrayRef arr, NFuint index) 
{
    NF_ASSERT_VAL(arr, NULL); 
    NF_ASSERT_VAL(index < arr->size, NULL); 

    return arr->data + ArrayOffset(arr, index); 
}

const NFvoid *NFArrayGetConstRef(NFArrayConstRef arr, NFuint index) 
{
    NF_ASSERT_VAL(arr, NULL); 
    NF_ASSERT_VAL(index < arr->size, NULL); 

    return arr->data + ArrayOffset(arr, index); 
}

NFvoid NFArraySetRange(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    NF_ASSERT(arr); 
    NF_ASSERT(index <= arr->size); 
    NF_RETURN_ON_FAIL(count); 
    
    if (arr->size < index + count) ArrayResize(arr, index + count, NF_FALSE); 

    NFCopyMemory(arr->data + ArrayOffset(arr, index), data, ArrayOffset(arr, count)); 
} 

NFvoid NFArrayAppendRange(NFArrayRef arr, NFuint count, const NFvoid *data) 
{
    NFuint oldSize; 

    NF_ASSERT(arr); 
    NF_RETURN_ON_FAIL(count); 

    oldSize = arr->size; 

    ArrayResize(arr, arr->size + count, NF_FALSE); 
    NFCopyMemory(arr->data + ArrayOffset(arr, oldSize), data, ArrayOffset(arr, count)); 
} 

NFvoid NFArrayInsertRange(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data) 
{
    NF_ASSERT(arr); 
    NF_ASSERT(index <= arr->size); 
    NF_RETURN_ON_FAIL(count); 
    
    ArrayResize(arr, arr->size + count, NF_FALSE); 

    if (index < arr->size) 
    {
        // move values 
        NFMoveMemory(arr->data + ArrayOffset(arr, index + count), arr->data + ArrayOffset(arr, index), ArrayOffset(arr, arr->size - index - count)); 
        NFCopyMemory(arr->data + ArrayOffset(arr, index), data, ArrayOffset(arr, count)); 
    }
    else 
    {
        // append values 
        NFArrayAppendRange(arr, count, data); 
    }
} 

NFvoid NFArrayRemoveRange(NFArrayRef arr, NFuint index, NFuint count) 
{
    NFuint oldSize; 

    NF_ASSERT(arr); 
    NF_ASSERT(index + count <= arr->size); 
    NF_RETURN_ON_FAIL(count); 

    oldSize = arr->size; 
    arr->size -= count; 

    NFMoveMemory(arr->data + ArrayOffset(arr, index), arr->data + ArrayOffset(arr, index + count), ArrayOffset(arr, count)); 
} 
