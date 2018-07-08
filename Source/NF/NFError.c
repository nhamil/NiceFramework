#include "NF/NFError.h" 

#include <stdio.h> 
#include <stdlib.h> 

static NFvoid DefaultErrorHandler(NFError err) 
{
    printf("NF FATAL ERROR (%d): %s\n", err, NFErrorMessage(err)); 
}

static NFErrorHandler errorHandler = NULL; 

NFvoid NFSetErrorHandler(NFErrorHandler handler) 
{
    errorHandler = handler; 
}

NFvoid NFFatalError(NFError err) 
{
    if (errorHandler) 
    {
        errorHandler(err); 
    }
    else 
    {
        DefaultErrorHandler(err); 
    }
    exit(err); 
}

const NFbyte *NFErrorMessage(NFError err) 
{
    switch (err) 
    {
    case NF_NO_ERROR: return "No error"; 
    case NF_ASSERTION_FAILED: return "Assertion failed"; 
    case NF_OUT_OF_MEMORY: return "Out of memory"; 
    case NF_INVALID_OPERATION: return "Invalid operation"; 
    default: return "Unknown error"; 
    }
}