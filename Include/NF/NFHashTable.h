#pragma once 

#ifndef NF_HASHTABLE_H 
#define NF_HASHTABLE_H 

#include "NF/NFCommon.h" 
#include "NF/NFFunc.h" 

typedef struct NFHashTable *NFHashTableRef; 

typedef const struct NFHashTable *NFHashTableConstRef; 

NFHashTableRef NFHashTableCreate(NFulong keySize, NFulong valueSize, NFEqualFunc equalFunc, NFHashFunc hashFunc); 

NFvoid NFHashTableDestroy(NFHashTableRef table); 

NFuint NFHashTableSize(NFHashTableConstRef table); 

NFdouble NFHashTableLoadFactor(NFHashTableConstRef table); 

NFuint NFHashTableBucketCount(NFHashTableConstRef table); 

NFbool NFHashTableGet(NFHashTableConstRef table, const NFvoid *key, NFvoid *value); 

NFvoid NFHashTablePut(NFHashTableRef table, const NFvoid *key, const NFvoid *value); 

NFvoid NFHashTableRemove(NFHashTableRef table, const NFvoid *key); 

#endif 