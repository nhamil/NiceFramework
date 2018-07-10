#include <NF/NFArray.h> 
#include <NF/NFError.h> 
#include <NF/NFHashTable.h> 

#include <stdio.h> 

int ArrayTest(void); 
int HashTableTest(void); 

int main(int argc, char **argv) 
{
    return ArrayTest(); 
}

void PrintArray(NFArrayConstRef list) 
{
    const NFuint *value; 
    NFuint i, size = NFArraySize(list); 
    printf("NFArray = ["); 
    for (i = 0; i < size; i++) 
    {
        if (i) printf(", "); 
        value = NFArrayGetConstRef(list, i); 
        printf("%d", *value); 
    }
    printf("]\n"); 
}

int ArrayTest(void) 
{
    NFArrayRef list; 
    NFint i; 

    list = NFArrayCreateOf(NFint);  

    for (i = 0; i < 9; i++) 
    {
        NFArrayAppend(list, &i); 
    }

    // 0, 1, 2, 3, 4, 5, 6, 7, 8 
    PrintArray(list); 

    NFint arr[] = { 9, 0 }; 
    NFArrayInsertRange(list, 3, 2, arr); 

    // 0, 1, 2, 9, 0, 3, 4, 5, 6, 7, 8 
    PrintArray(list); 

    i = 1; 
    NFArraySet(list, 6, &i); 

    // 0, 1, 2, 9, 0, 3, 1, 5, 6, 7, 8 
    PrintArray(list); 

    NFArrayRemoveRange(list, 7, 3); 

    // 0, 1, 2, 9, 0, 3, 1, 8 
    PrintArray(list); 

    NFArrayDestroy(list); 

    return 0; 
}

#if 0 
void PrintHashTableEntry(NFHashTableConstRef map, int key) 
{
    int value = -1; 
    NFbool valid = NFGetHashTable(map, &key, &value); 

    printf("%d : ", key); 

    if (valid) 
    {
        printf("%d\n", value); 
    }
    else 
    {
        printf("invalid\n"); 
    }
}

int HashTableTest(void) 
{
    NFHashTableRef map = NFCreateHashTable(sizeof (int), sizeof (int), NULL, NULL); 

    NFint key, value; 
    NFbool valid; 

    // put 

    key = 123; 
    value = 321; 
    NFPutHashTable(map, &key, &value); 

    key = 12; 
    value = 144; 
    NFPutHashTable(map, &key, &value); 

    // get 

    PrintHashTableEntry(map, 1); 
    PrintHashTableEntry(map, 12); 
    PrintHashTableEntry(map, 122); 
    PrintHashTableEntry(map, 123); 
    
    NFDestroyHashTable(map); 
}
#endif 
