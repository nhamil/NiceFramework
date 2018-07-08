#pragma once 

#ifndef NF_ARRAY_H  
#define NF_ARRAY_H 

#include "NF/NFCommon.h" 

NF_EXTERN_C_BEGIN 

typedef struct NFArray *NFArrayRef; 

typedef const struct NFArray *NFArrayConstRef; 

NFArrayRef NFCreateArray(NFulong elemSize, NFuint count, const NFvoid *data); 

NFvoid NFDestroyArray(NFArrayRef arr); 

NFuint NFArraySize(NFArrayConstRef arr); 

NFulong NFArrayElemSize(NFArrayConstRef arr); 

NFbool NFGetArray(NFArrayConstRef arr, NFuint index, NFuint count, NFvoid *data); 

NFvoid NFSetArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

NFvoid NFAppendArray(NFArrayRef arr, NFuint count, const NFvoid *data); 

NFvoid NFInsertArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

NFvoid NFRemoveArray(NFArrayRef arr, NFuint index, NFuint count); 

NF_EXTERN_C_FINISH 

#endif 