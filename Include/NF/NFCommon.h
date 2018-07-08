#pragma once 

#ifndef NF_COMMON_H 
#define NF_COMMON_H 

#include <stdint.h> 
#include <stdlib.h> 

#ifdef __cplusplus 
#define NF_EXTERN_C_BEGIN extern "C" { 
#define NF_EXTERN_C_FINISH } 
#else 
#define NF_EXTERN_C_BEGIN 
#define NF_EXTERN_C_FINISH 
#endif 

#define NF_RETURN_ON_FAIL(x) if (!x) return; 
#define NF_RETURN_VAL_ON_FAIL(x, val) if (!x) return val; 

NF_EXTERN_C_BEGIN 

#define NF_TRUE (1) 
#define NF_FALSE (0) 

typedef int8_t NFbool; 

typedef int8_t NFbyte; 
typedef int16_t NFshort; 
typedef int32_t NFint; 
typedef int64_t NFlong; 

typedef uint8_t NFubyte; 
typedef uint16_t NFushort; 
typedef uint32_t NFuint; 
typedef uint64_t NFulong; 

typedef float NFfloat; 
typedef double NFdouble; 

typedef void NFvoid; 

NF_EXTERN_C_FINISH 

#endif 