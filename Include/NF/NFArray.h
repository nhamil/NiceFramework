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
 * @returns Size of array
 */ 
NFuint NFArraySize(NFArrayConstRef arr); 

/**
 * Gets the element size of an array. 
 * 
 * @returns Element size of array 
 */ 
NFulong NFArrayElemSize(NFArrayConstRef arr); 

/**
 * Gets an element of an array. 
 * 
 * @param data Output of array elements
 */
#define NFGetArray(arr, index, data) NFGetArrayRange(arr, index, 1, data) 

/**
 * Gets elements of an array. 
 * 
 * @param data Output of array elements
 */
NFvoid NFGetArrayRange(NFArrayConstRef arr, NFuint index, NFuint count, NFvoid *data); 

/**
 * Sets an element of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
#define NFSetArray(arr, index, data) NFSetArrayRange(arr, index, 1, data) 

/**
 * Sets elements of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
NFvoid NFSetArrayRange(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

/**
 * Appends an element to the end of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
#define NFAppendArray(arr, data) NFAppendArrayRange(arr, 1, data) 

/**
 * Appends elements to the end of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
NFvoid NFAppendArrayRange(NFArrayRef arr, NFuint count, const NFvoid *data); 

/**
 * Inserts an element into an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
#define NFInsertArray(arr, index, data) NFInsertArrayRange(arr, index, 1, data) 

/**
 * Inserts elements into an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
NFvoid NFInsertArrayRange(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

/**
 * Removes an element from an array. 
 */
#define NFRemoveArray(arr, index) NFRemoveArrayRange(arr, index, 1) 

/**
 * Removes elements from an array. 
 */
NFvoid NFRemoveArrayRange(NFArrayRef arr, NFuint index, NFuint count); 

NF_EXTERN_C_FINISH 

#endif 