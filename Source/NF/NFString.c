#include "NF/NFString.h" 

#include "NF/NFMemory.h" 

#include <string.h> 

struct NFString 
{
    NFbyte *string; 
    NFuint size; 
    NFuint capacity; 
};

NFStringRef StringCreatePtrSize(NFuint size, const NFbyte *data) 
{
    NFStringRef str = NFNewStruct(1, NFString); 
    str->string = NFMalloc(size + 1, 1); 
    str->size = size; 
    str->capacity = size + 1; 

    NFCopyMemory(str->string, data, size); 
    str->string[size] = 0; 

    return str; 
} 

NFvoid StringReserve(NFStringRef str, NFuint size) 
{
    NFuint cap = size + 1; 
    if (str->capacity < cap) 
    {
        str->capacity = cap; 
        str->string = NFRealloc(str->string, cap, 1); 
    }
}

NFbool StringEquals(NFuint size, NFuint offA, const NFbyte *a, NFuint offB, const NFbyte *b) 
{
    NFuint i; 
    for (i = 0; i < size; i++) 
    {
        if (a[offA + i] != b[offB + i]) return NF_FALSE; 
    }
    return NF_TRUE; 
}

NFStringRef NFStringCreate(const NFbyte *data) 
{
    NF_ASSERT_VAL(data, NULL); 

    return StringCreatePtrSize(strlen(data), data); 
} 

NFStringRef NFStringCreateCopy(NFStringConstRef from) 
{
    NF_ASSERT_VAL(from, NULL); 

    return StringCreatePtrSize(from->size, from->string); 
}

NFStringRef NFStringCreateSubstring(NFStringConstRef from, NFuint start, NFuint count) 
{
    NF_ASSERT_VAL(from, NULL); 
    NF_ASSERT_VAL(start + count <= from->size, NULL); 

    return StringCreatePtrSize(count, &from->string[start]); 
} 

NFvoid NFStringDestroy(NFStringRef str) 
{
    NF_ASSERT(str); 

    NFFree(str->string); 
    NFFree(str); 
}

NFvoid NFStringGetRange(NFStringConstRef str, NFuint start, NFuint count, NFbyte *buffer) 
{
    NF_ASSERT(str); 
    NF_ASSERT(start + count <= str->size); 

    NFCopyMemory(buffer, &str->string[start], count); 
}

NFuint NFStringLength(NFStringConstRef str) 
{
    NF_ASSERT_VAL(str, 0U); 

    return str->size; 
}

NFbyte NFStringCharAt(NFStringConstRef str, NFuint index) 
{
    NF_ASSERT_VAL(str, 0); 
    NF_ASSERT_VAL(index < str->size, 0); 

    return str->string[index]; 
}

const NFbyte *NFStringCString(NFStringConstRef str) 
{
    NF_ASSERT_VAL(str, NULL); 
    
    return str->string; 
}

NFulong NFStringToULong(NFStringConstRef str, NFbool *status) 
{
    NF_ASSERT_VAL(str, 0ULL); 

    NFulong out = 0; 

    NFuint i; 
    for (i = 0; i < str->size; i++) 
    {
        NFbyte c = str->string[i]; 

        if (c < '0' || c > '9') 
        {
            if (status) *status = NF_FALSE; 
            return 0ULL; 
        }

        out = out * 10 + (c - '0'); 
    }

    if (status) *status = NF_TRUE; 
    return out; 
}

NFuint NFStringToUInt(NFStringConstRef str, NFbool *status) 
{
    NF_ASSERT_VAL(str, 0U); 

    return (NFuint) NFStringToULong(str, status); 
}

NFdouble NFStringToDouble(NFStringConstRef str, NFbool *status) 
{
    NF_ASSERT_VAL(str, 0.0); 

    NFuint i; 
    NFdouble out = 0.0; 
    NFdouble decimal = 0.1; 
    NFbool period = NF_FALSE; 
    for (i = 0; i < str->size; i++) 
    {
        NFbyte c = str->string[i]; 

        if (c < '0' || c > '9') 
        {
            if (!period && c == '.') 
            {
                period = NF_TRUE; 
            }
            else 
            {
                if (status) *status = NF_FALSE; 
                return 0.0; 
            }
        }
        else 
        {
            if (period) 
            {
                out += decimal * (c - '0'); 
                decimal *= 0.1; 
            }
            else 
            {
                out = out * 10 + (c - '0'); 
            }
        }
    }

    if (status) *status = NF_TRUE; 
    return out; 
}

NFbool NFStringStartsWith(NFStringConstRef str, NFStringConstRef start) 
{
    NF_ASSERT_VAL(str && start, NF_FALSE); 

    if (start->size > str->size) return NF_FALSE; 

    return StringEquals(start->size, 0, str->string, 0, start->string); 
}

NFbool NFStringEndsWith(NFStringConstRef str, NFStringConstRef end) 
{
    NF_ASSERT_VAL(str && end, NF_FALSE); 

    if (end->size > str->size) return NF_FALSE; 

    NFuint offset = str->size - end->size; 
    return StringEquals(end->size, offset, str->string, 0, end->string); 
}

NFuint NFStringIndexOf(NFStringConstRef str, NFStringConstRef find, NFbool *found) 
{
    NF_ASSERT_VAL(str && find, 0); 

    if (find->size > str->size) 
    {
        if (found) *found = NF_FALSE; 
        return 0; 
    }

    NFuint i; 
    NFuint max = str->size - find->size + 1; 
    for (i = 0; i < max; i++) 
    {
        NFuint j; 
        NFbool equal = StringEquals(find->size, i, str->string, 0, find->string); 

        if (equal) 
        {
            if (found) *found = NF_TRUE; 
            return i; 
        }
    }

    if (found) *found = NF_FALSE; 
    return 0; 
}

NFvoid NFStringAppend(NFStringRef str, NFStringConstRef other) 
{
    NF_ASSERT(str && other); 

    NFuint newSize = str->size + other->size; 
    StringReserve(str, newSize); 
    str->string[newSize] = 0; 

    NFCopyMemory(&str->string[str->size], other->string, other->size); 
    str->size = newSize; 
}

NFvoid NFStringInsert(NFStringRef str, NFuint index, NFStringConstRef other) 
{
    NF_ASSERT(str && other); 

    StringReserve(str, str->size + other->size); 
    NFMoveMemory(&str->string[index + other->size], &str->string[index], str->size - index); 
    NFCopyMemory(&str->string[index], other->string, other->size); 
    str->size += other->size; 
    str->string[str->size] = 0; 
}

NFvoid NFStringRemove(NFStringRef str, NFuint index, NFuint count) 
{
    NF_ASSERT(str); 
    NF_ASSERT(index + count <= str->size); 

    NFMoveMemory(&str->string[index], &str->string[index + count], str->size - index - count); 
    str->size -= count; 
    str->string[str->size] = 0; 
}

NFvoid NFStringReplace(NFStringRef str, NFStringConstRef what, NFStringConstRef with) 
{
    NF_ASSERT(str); 
    NF_ASSERT(what); 

    NFuint incr = with ? with->size : 1; 
    NFuint i = 0; 
    while (i < str->size) 
    {
        NFbool found = StringEquals(what->size, i, str->string, 0, what->string); 
        
        if (found) 
        {
            NFStringRemove(str, i, what->size); 
            if (with) NFStringInsert(str, i, with); 
            i += incr; 
        }
        else 
        {
            i++; 
        }
    }
}
