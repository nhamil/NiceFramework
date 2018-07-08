#include <NF/NFArray.h> 

#include <stdio.h> 

int main(int argc, char **argv) 
{
    NFArrayRef list; 
    NFint i, value, size; 

    list = NFCreateArray(sizeof (NFint), 0, NULL); 

    for (i = 0; i < 10; i++) 
    {
        NFAppendArray(list, 1, &i); 
    }

    size = NFArraySize(list); 

    printf("NFArray = ["); 
    for (i = 0; i < size; i++) 
    {
        if (i) printf(", "); 
        NFGetArray(list, i, 1, &value); 
        printf("%d", value); 
    }
    printf("]\n"); 

    return 0; 
}