#pragma once 

#ifndef NF_ARRAY_H  
#define NF_ARRAY_H 

#include "NF/NFCommon.h" 

/**
 * Shorthand for creating an array of type [type] 
 */ 
#define NFCreateArrayOf(type) NFCreateArray(sizeof (type), 0, NULL) 

/** 
 * Shorthand for creating an array of type [type] 
 * with initial data 
 */ 
#define NFCreateAndSetArrayOf(type, count, data) NFCreateArray(sizeof (type), count, data) 

NF_EXTERN_C_BEGIN 

/**
 * Mutable array pointer 
 */
typedef struct NFArray *NFArrayRef; 

/** 
 * Immutable array pointer 
 */ 
typedef const struct NFArray *NFArrayConstRef; 

/**
 * Creates an array 
 * 
 * @param elemSize Size of one element: sizeof (Type) 
 * @param count Number of starting elements 
 * @param data Starting data, will be zeroed if NULL 
 */
NFArrayRef NFCreateArray(NFulong elemSize, NFuint count, const NFvoid *data); 

/**
 * Destroys an array 
 */ 
NFvoid NFDestroyArray(NFArrayRef arr); 

/**
 * Gets the size of an array. 
 * 
 * @returns Size of array or 0 if [arr] is NULL 
 */ 
NFuint NFArraySize(NFArrayConstRef arr); 

/**
 * Gets the element size of an array. 
 * 
 * @returns Element size of array or 0 if [arr] is NULL 
 */ 
NFulong NFArrayElemSize(NFArrayConstRef arr); 

/**
 * Gets elements of an array. 
 * 
 * @param data Output of array elements, or zeroed if invalid parameters 
 * @returns Whether operation was successful 
 */
NFbool NFGetArray(NFArrayConstRef arr, NFuint index, NFuint count, NFvoid *data); 

/**
 * Sets elements of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 * @returns Whether operation was successful 
 */
NFbool NFSetArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

/**
 * Appends elements to the end of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 * @returns Whether operation was successful 
 */
NFbool NFAppendArray(NFArrayRef arr, NFuint count, const NFvoid *data); 

/**
 * Inserts elements into an array. 
 * 
 * @param data Input for array elements, can be NULL 
 * @returns Whether operation was successful 
 */
NFbool NFInsertArray(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

/**
 * Removes elements from an array. 
 * 
 * @returns Whether operation was successful 
 */
NFbool NFRemoveArray(NFArrayRef arr, NFuint index, NFuint count); 

NF_EXTERN_C_FINISH 

#endif 