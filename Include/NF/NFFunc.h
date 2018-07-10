#pragma once 

#ifndef NF_FUNC_H 
#define NF_FUNC_H 

#include "NF/NFCommon.h" 

typedef NFbool (*NFEqualFunc)(const NFvoid *a, const NFvoid *b); 

typedef NFuint (*NFHashFunc)(const NFvoid *data); 

#endif 