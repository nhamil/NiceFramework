#pragma once 

#ifndef NF_ERROR_H 
#define NF_ERROR_H 

#include "NF/NFCommon.h" 

typedef enum NFError NFError; 

enum NFError 
{
    NF_NO_ERROR, 
    NF_ASSERTION_FAILED, 
    NF_OUT_OF_MEMORY, 
    NF_INVALID_OPERATION, 
};

typedef NFvoid (*NFErrorHandler)(NFError err); 

NFvoid NFSetErrorHandler(NFErrorHandler handler); 

NFvoid NFFatalError(NFError err); 

const NFbyte *NFErrorMessage(NFError err); 

#endif 