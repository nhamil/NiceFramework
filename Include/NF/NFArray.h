#pragma once 

#ifndef NF_ARRAY_H  
#define NF_ARRAY_H 

#include "NF/NFCommon.h" 

/**
 * Shorthand for creating an array of type [type] 
 */ 
#define NFArrayCreateOf(type) NFArrayCreate(sizeof (type), 0, NULL) 

/** 
 * Shorthand for creating an array of type [type] 
 * with initial data 
 */ 
#define NFArrayCreateAndSetOf(type, count, data) NFArrayCreate(sizeof (type), count, data) 

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
NFArrayRef NFArrayCreate(NFulong elemSize, NFuint count, const NFvoid *data); 

/**
 * Destroys an array 
 */ 
NFvoid NFArrayDestroy(NFArrayRef arr); 

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
#define NFArrayGet(arr, index, data) NFArrayGetRange(arr, index, 1, data) 

/**
 * Gets elements of an array. 
 * 
 * @param data Output of array elements
 */
NFvoid NFArrayGetRange(NFArrayConstRef arr, NFuint index, NFuint count, NFvoid *data); 

/**
 * Gets reference to array index 
 */
NFvoid *NFArrayGetRef(NFArrayRef arr, NFuint index); 

/** 
 * Gets constant reference to array index 
 */ 
const NFvoid *NFArrayGetConstRef(NFArrayConstRef arr, NFuint index); 

/**
 * Sets an element of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
#define NFArraySet(arr, index, data) NFArraySetRange(arr, index, 1, data) 

/**
 * Sets elements of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
NFvoid NFArraySetRange(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

/**
 * Appends an element to the end of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
#define NFArrayAppend(arr, data) NFArrayAppendRange(arr, 1, data) 

/**
 * Appends elements to the end of an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
NFvoid NFArrayAppendRange(NFArrayRef arr, NFuint count, const NFvoid *data); 

/**
 * Inserts an element into an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
#define NFArrayInsert(arr, index, data) NFArrayInsertRange(arr, index, 1, data) 

/**
 * Inserts elements into an array. 
 * 
 * @param data Input for array elements, can be NULL 
 */
NFvoid NFArrayInsertRange(NFArrayRef arr, NFuint index, NFuint count, const NFvoid *data); 

/**
 * Removes an element from an array. 
 */
#define NFArrayRemove(arr, index) NFArrayRemoveRange(arr, index, 1) 

/**
 * Removes elements from an array. 
 */
NFvoid NFArrayRemoveRange(NFArrayRef arr, NFuint index, NFuint count); 

NF_EXTERN_C_FINISH 

#endif 