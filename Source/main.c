#include <NF/NFArray.h> 
#include <NF/NFError.h> 

#include <stdio.h> 

void PrintArray(NFArrayConstRef list) 
{
    NFuint i, value, size = NFArraySize(list); 
    printf("NFArray = ["); 
    for (i = 0; i < size; i++) 
    {
        if (i) printf(", "); 
        NFGetArray(list, i, &value); 
        printf("%d", value); 
    }
    printf("]\n"); 
}

int main(int argc, char **argv) 
{
    NFArrayRef list; 
    NFint i; 

    list = NFCreateArrayOf(NFint);  

    for (i = 0; i < 9; i++) 
    {
        NFAppendArray(list, &i); 
    }

    // 0, 1, 2, 3, 4, 5, 6, 7, 8 
    PrintArray(list); 

    NFint arr[] = { 9, 0 }; 
    NFInsertArrayRange(list, 3, 2, arr); 

    // 0, 1, 2, 9, 0, 3, 4, 5, 6, 7, 8 
    PrintArray(list); 

    i = 1; 
    NFSetArray(list, 6, &i); 

    // 0, 1, 2, 9, 0, 3, 1, 5, 6, 7, 8 
    PrintArray(list); 

    NFRemoveArrayRange(list, 7, 3); 

    // 0, 1, 2, 9, 0, 3, 1, 8 
    PrintArray(list); 

    NFDestroyArray(list); 

    return 0; 
}