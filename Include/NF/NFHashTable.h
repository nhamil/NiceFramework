#pragma once 

#ifndef NF_HASHTABLE_H 
#define NF_HASHTABLE_H 

#include "NF/NFCommon.h" 
#include "NF/NFFunc.h" 

typedef struct NFHashTable *NFHashTableRef; 

typedef const struct NFHashTable *NFHashTableConstRef; 

NFHashTableRef NFHashTableCreate(NFulong keySize, NFulong valueSize, NFEqualFunc equalFunc, NFHashFunc hashFunc); 

NFvoid NFHashTableDestroy(NFHashTableRef map); 

NFbool NFHashTableGet(NFHashTableConstRef map, const NFvoid *key, NFvoid *value); 

NFvoid NFHashTablePut(NFHashTableRef map, const NFvoid *key, const NFvoid *value); 

NFvoid NFHashTableRemove(NFHashTableRef map, const NFvoid *key); 

#endif 