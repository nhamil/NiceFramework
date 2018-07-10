#if 0

#include "NF/NFHashTable.h" 

#include "NF/NFArray.h" 
#include "NF/NFMemory.h" 

typedef struct Entry Entry; 

struct NFHashTable 
{   
    Entry *buckets; 
    NFuint bucketCount; 
    NFulong keySize; 
    NFulong valueSize; 
    NFEqualFunc equalFunc; 
    NFHashFunc hashFunc; 
};

struct Entry 
{
    NFvoid *key; 
    NFvoid *value; 
    Entry *next; 
};

NFvoid InitEntry(Entry *e, NFulong keySize, NFulong valueSize) 
{
    e->key = NFMalloc(1, keySize); 
    e->value = NFMalloc(1, valueSize); 
    e->next = NULL; 
}

NFvoid InitBucket(Bucket *b, NFulong keySize, NFulong valueSize) 
{
    b->keys = NFCreateArray(keySize, 0, NULL); 
    b->values = NFCreateArray(valueSize, 0, NULL); 
}

NFvoid DestroyBucket(Bucket *b) 
{
    NFDestroyArray(b->keys); 
    NFDestroyArray(b->values); 
}

NFuint QuickHash(const NFvoid *key, NFulong size) 
{
    NFuint hash = 13; 

    for (NFulong i = 0; i < size; i++) 
    {
        hash *= 31 * ((NFbyte *) key)[i]; 
    }

    return hash; 
}

NFuint GetHash(NFHashTableConstRef map, const NFvoid *key) 
{
    NFHashFunc hash = map->hashFunc; 

    if (hash) 
    {
        return hash(key); 
    }
    else 
    {
        return QuickHash(key, map->keySize); 
    }
}

NFbool GetEqual(NFHashTableConstRef map, const NFvoid *a, const NFvoid *b) 
{
    NFEqualFunc equal = map->equalFunc; 

    if (equal) 
    {
        return equal(a, b); 
    }
    else 
    {
        return NFCompareMemory(a, b, map->keySize); 
    }
}

NFHashTableRef NFCreateHashTable(NFulong keySize, NFulong valueSize, NFEqualFunc equalFunc, NFHashFunc hashFunc) 
{
    NF_ASSERT_VAL(keySize && valueSize, NULL); 
    
    NFHashTableRef map = NFNewStruct(1, NFHashTable); 

    map->buckets = NFNewStruct(11, Bucket); 
    map->bucketCount = 11; 
    map->keySize = keySize; 
    map->valueSize = valueSize; 
    map->equalFunc = equalFunc; 
    map->hashFunc = hashFunc; 

    for (NFuint i = 0; i < map->bucketCount; i++) 
    {
        InitBucket(&map->buckets[i], keySize, valueSize); 
    }

    return map; 
}

NFvoid NFDestroyHashTable(NFHashTableRef map) 
{
    NF_RETURN_ON_FAIL(map); 

    for (NFuint i = 0; i < map->bucketCount; i++) 
    {
        DestroyBucket(&map->buckets[i]); 
    }

    NFFree(map); 
}

NFbool NFGetHashTable(NFHashTableConstRef map, const NFvoid *key, NFvoid *value) 
{
    NF_ASSERT_VAL(map && key, NF_FALSE); 

    NFuint hash = GetHash(map, key); 

    NFuint bIndex = hash % map->bucketCount; 

    Bucket *bucket = &map->buckets[bIndex]; 

    for (NFuint i = 0; i < bucket->size; i++) 
    {

    }

    // could not find 

    if (value) NFZeroMemory(value, map->valueSize); 

    return NF_FALSE; 
}

NFvoid NFPutHashTable(NFHashTableRef map, const NFvoid *key, const NFvoid *value) 
{

}

#endif 