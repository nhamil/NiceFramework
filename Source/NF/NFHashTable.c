#include "NF/NFHashTable.h" 

#include "NF/NFCommon.h" 
#include "NF/NFFunc.h" 
#include "NF/NFMemory.h" 

typedef struct Entry Entry; 

#define NF_START_BUCKETS (17) 
#define NF_NEXT_BUCKETS(n) (((n) - 1) * 2 + 1) 

struct NFHashTable 
{   
    Entry **buckets; 
    NFuint bucketCount; 
    NFulong keySize; 
    NFulong valueSize; 
    NFEqualFunc equalFunc; 
    NFHashFunc hashFunc; 
    NFuint size; 
};

struct Entry 
{
    NFvoid *key; 
    NFvoid *value; 
    Entry *next; 
};

Entry *EntryCreate(NFulong keySize, NFulong valueSize) 
{
    Entry *e = NFNewStruct(1, Entry); 
    e->key = NFMalloc(1, keySize); 
    e->value = NFMalloc(1, valueSize); 
    e->next = NULL; 
}

NFvoid EntryDestroy(Entry *e) 
{
    Entry *cur = e; 
    Entry *tmp; 

    while (cur) 
    {
        tmp = cur->next; 
        NFFree(cur->key); 
        NFFree(cur->value); 
        NFFree(cur); 
        cur = tmp; 
    }
}

NFuint QuickHash(const NFvoid *key, NFulong size) 
{
    // from FNV Hash 
    NFulong i; 
    NFuint hash = 0x811c9dc5; 

    for (i = 0; i < size; i++) 
    {
        hash ^= ((NFbyte *) key)[i]; 
        hash *= 16777619; 
    }

    return hash; 
}

NFuint GetHash(NFHashTableConstRef table, const NFvoid *key) 
{
    NFHashFunc hash = table->hashFunc; 

    if (hash) 
    {
        return hash(key); 
    }
    else 
    {
        return QuickHash(key, table->keySize); 
    }
}

NFbool GetEqual(NFHashTableConstRef table, const NFvoid *a, const NFvoid *b) 
{
    NFEqualFunc equal = table->equalFunc; 

    if (equal) 
    {
        return equal(a, b); 
    }
    else 
    {
        return NFCompareMemory(a, b, table->keySize) == 0; 
    }
}

NFvoid GrowBucketsIfNeeded(NFHashTableRef table) 
{
    NFdouble ratio = (NFdouble) table->size / table->bucketCount; 

    if (ratio > 0.667) 
    {
        NFuint i; 
        NFuint newBucketCount = NF_NEXT_BUCKETS(table->bucketCount); 
        Entry **newBuckets = NFNewStruct(newBucketCount, Entry *); 

        for (i = 0; i < newBucketCount; i++) 
        {
            newBuckets[i] = NULL; 
        }

        for (i = 0; i < table->bucketCount; i++) 
        {
            Entry *entry = table->buckets[i]; 

            while (entry) 
            {
                Entry *next = entry->next; 
                NFuint index = GetHash(table, entry->key) % newBucketCount; 

                Entry *first = newBuckets[index]; 

                newBuckets[index] = entry; 
                entry->next = first; 

                entry = next; 
            }
        }

        NFFree(table->buckets); 

        table->bucketCount = newBucketCount; 
        table->buckets = newBuckets; 
    }
}

NFHashTableRef NFHashTableCreate(NFulong keySize, NFulong valueSize, NFEqualFunc equalFunc, NFHashFunc hashFunc) 
{
    NF_ASSERT_VAL(keySize && valueSize, NULL); 
    
    NFHashTableRef table = NFNewStruct(1, NFHashTable); 
    NFuint i; 

    table->buckets = NFNewStruct(NF_START_BUCKETS, Entry *); 
    table->bucketCount = NF_START_BUCKETS; 
    table->keySize = keySize; 
    table->valueSize = valueSize; 
    table->equalFunc = equalFunc; 
    table->hashFunc = hashFunc; 
    table->size = 0; 

    for (i = 0; i < table->bucketCount; i++) 
    {
        table->buckets[i] = NULL; 
    }

    return table; 
}

NFvoid NFHashTableDestroy(NFHashTableRef table) 
{
    NF_RETURN_ON_FAIL(table); 

    NFuint i; 

    for (i = 0; i < table->bucketCount; i++) 
    {
        EntryDestroy(table->buckets[i]); 
    }

    NFFree(table->buckets); 
    NFFree(table); 
}

NFuint NFHashTableSize(NFHashTableConstRef table) 
{
    NF_ASSERT_VAL(table, 0U); 

    return table->size; 
}

NFdouble NFHashTableLoadFactor(NFHashTableConstRef table) 
{
    NF_ASSERT_VAL(table, 0.0); 

    return (NFdouble) table->size / table->bucketCount; 
}

NFuint NFHashTableBucketCount(NFHashTableConstRef table) 
{
    NF_ASSERT_VAL(table, 0U); 

    return table->bucketCount; 
}

NFbool NFHashTableGet(NFHashTableConstRef table, const NFvoid *key, NFvoid *value) 
{
    NF_ASSERT_VAL(table && key, NF_FALSE); 

    NFuint i; 
    NFuint hash = GetHash(table, key); 
    NFuint bIndex = hash % table->bucketCount; 

    Entry *entry = table->buckets[bIndex]; 
    NFuint multi = 0; 

    while (entry) 
    {
        if (GetEqual(table, entry->key, key)) 
        {
            if (value) NFCopyMemory(value, entry->value, table->valueSize); 
            return NF_TRUE; 
        }
        entry = entry->next; 
        multi++; 
    }

    // could not find 

    if (value) NFZeroMemory(value, table->valueSize); 
    return NF_FALSE; 
}

NFvoid NFHashTablePut(NFHashTableRef table, const NFvoid *key, const NFvoid *value) 
{
    NF_ASSERT(table && key); 

    GrowBucketsIfNeeded(table); 

    NFuint hash = GetHash(table, key); 
    NFuint bIndex = hash % table->bucketCount; 

    Entry *parent = NULL; 
    Entry *entry = table->buckets[bIndex]; 

    while (entry) 
    {
        if (GetEqual(table, entry->key, key)) 
        {
            NFCopyMemory(entry->value, value, table->valueSize); 
            return; 
        }

        parent = entry; 
        entry = entry->next; 
    }

    // entry not yet created 
    table->size++; 

    entry = EntryCreate(table->keySize, table->valueSize); 
    NFCopyMemory(entry->key, key, table->keySize); 
    NFCopyMemory(entry->value, value, table->valueSize); 

    if (parent) 
    {
        parent->next = entry; 
    }
    else 
    {
        table->buckets[bIndex] = entry; 
    }
}

NFvoid NFHashTableRemove(NFHashTableRef table, const NFvoid *key) 
{
    NF_ASSERT(table && key); 

    NFuint hash = GetHash(table, key); 
    NFuint bIndex = hash % table->bucketCount; 

    Entry *parent = NULL; 
    Entry *entry = table->buckets[bIndex]; 

    while (entry) 
    {
        if (GetEqual(table, entry->key, key)) 
        {
            table->size--; 
            // remove single entry 
            Entry *next = entry->next; 
            entry->next = NULL; 
            EntryDestroy(entry); 

            if (parent) 
            {
                parent->next = next; 
            }
            else 
            {
                table->buckets[bIndex] = next; 
            }
        }
        parent = entry; 
        entry = entry->next; 
    }

    // key was not in hash table at this point 
}
