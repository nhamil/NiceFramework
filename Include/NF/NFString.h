#pragma once 

#ifndef NF_STRING_H
#define NF_STRING_H 

#include "NF/NFCommon.h" 
#include "NF/NFArray.h" 

typedef struct NFString *NFStringRef; 

typedef const struct NFString *NFStringConstRef; 

NFStringRef NFStringCreate(const NFbyte *data); 

NFStringRef NFStringCreateCopy(NFStringConstRef from); 

NFStringRef NFStringCreateSubstring(NFStringConstRef from, NFuint start, NFuint count); 

NFvoid NFStringDestroy(NFStringRef str); 

NFvoid NFStringGetRange(NFStringConstRef str, NFuint start, NFuint count, NFbyte *buffer); 

NFuint NFStringLength(NFStringConstRef str); 

NFbyte NFStringCharAt(NFStringConstRef str, NFuint index); 

const NFbyte *NFStringCString(NFStringConstRef str); 

NFuint NFStringToUInt(NFStringConstRef str, NFbool *status); 

NFdouble NFStringToDouble(NFStringConstRef str, NFbool *status); 

NFbool NFStringStartsWith(NFStringConstRef str, NFStringConstRef start); 

NFbool NFStringEndsWith(NFStringConstRef str, NFStringConstRef end); 

NFuint NFStringIndexOf(NFStringConstRef str, NFStringConstRef find, NFbool *found); 

NFArrayRef NFStringSplit(NFStringConstRef str, NFStringConstRef split); 

NFvoid NFStringAppend(NFStringRef str, NFStringConstRef other); 

NFvoid NFStringInsert(NFStringRef str, NFuint index, NFStringConstRef other); 

NFvoid NFStringRemove(NFStringRef str, NFuint index, NFuint count); 

NFvoid NFStringReplace(NFStringRef str, NFStringConstRef what, NFStringConstRef with); 

#endif 
