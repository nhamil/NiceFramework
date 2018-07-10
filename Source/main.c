#include <NF/NFArray.h> 
#include <NF/NFError.h> 
#include <NF/NFHashTable.h> 
#include <NF/NFString.h> 

#include <stdio.h> 

int ArrayTest(void); 
int HashTableTest(void); 
int StringTest(void); 

int main(int argc, char **argv) 
{
    return StringTest(); 
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

void PrintHashTableEntry(NFHashTableConstRef table, int key) 
{
    int value = -1; 

    printf("%d : ", key); 

    if (NFHashTableGet(table, &key, &value)) 
    {
        printf("%d\n", value); 
    }
    else 
    {
        printf("null\n"); 
    }
}

int HashTableTest(void) 
{
    NFHashTableRef table = NFHashTableCreate(sizeof (int), sizeof (int), NULL, NULL); 

    NFint key, value; 
    NFbool valid; 

    // put 

    key = 123; 
    value = 321; 
    NFHashTablePut(table, &key, &value); 

    key = 12; 
    value = 144; 
    NFHashTablePut(table, &key, &value); 

    key = 123; 
    value = 4321; 
    NFHashTablePut(table, &key, &value); 

    printf("Buckets: %d, Load Factor: %f\n", NFHashTableBucketCount(table), NFHashTableLoadFactor(table)); 

    // get 

    PrintHashTableEntry(table, 1); 
    PrintHashTableEntry(table, 12); 
    PrintHashTableEntry(table, 122); 
    PrintHashTableEntry(table, 123); 

    printf("==========\n"); 

    // remove 

    key = 12; 
    NFHashTableRemove(table, &key); 

    key = 0; 
    NFHashTableRemove(table, &key); 

    printf("Buckets: %d, Load Factor: %f\n", NFHashTableBucketCount(table), NFHashTableLoadFactor(table)); 

    PrintHashTableEntry(table, 1); 
    PrintHashTableEntry(table, 12); 
    PrintHashTableEntry(table, 122); 
    PrintHashTableEntry(table, 123); 
    
    printf("==========\n"); 

    printf("Putting values...\n"); 

    int i; 
    for (i = 0; i < 30000; i++) 
    {
        value = i * 2 + 1; 
        NFHashTablePut(table, &i, &value); 
    }

    printf("Done!\n"); 

    printf("Buckets: %d, Load Factor: %f\n", NFHashTableBucketCount(table), NFHashTableLoadFactor(table)); 

    for (i = 0; i < 10; i++) PrintHashTableEntry(table, i); 

    PrintHashTableEntry(table, 12); 
    PrintHashTableEntry(table, 122); 
    PrintHashTableEntry(table, 123); 

    NFHashTableDestroy(table); 
}

int StringTest(void) 
{
    NFStringRef str = NFStringCreate("this is a test"); 
    NFStringRef str2 = NFStringCreate("123.45"); 
    NFStringRef substr = NFStringCreateSubstring(str, 2, 4); // "is i"
    
    printf("%s\n", NFStringCString(str)); 
    printf("%s\n", NFStringCString(substr)); 

    NFStringAppend(str, substr); // "this is a testis i" 

    printf("%s\n", NFStringCString(str)); 

    NFStringInsert(str, 1, str2); // "t123.45his is a testis i" 

    printf("%s\n", NFStringCString(str)); 

    NFStringRemove(str, 2, 1); 

    printf("%s\n", NFStringCString(str)); // "t13.45his is a testis i" 

    {
        NFbool found; 
        NFuint index = NFStringIndexOf(str, substr, &found); 

        if (found) 
        {
            printf("Index: %d\n", index); 
        }
        else 
        {
            printf("Index not found\n"); 
        }
    }

    printf("%d\n", NFStringToUInt(str, NULL)); // 0 
    printf("%d\n", NFStringToUInt(str2, NULL)); // 0 

    printf("%f\n", NFStringToDouble(str, NULL)); // 0
    printf("%f\n", NFStringToDouble(str2, NULL)); // 123.45 

    {
        NFStringRef tmp = NFStringCreate("is iis i"); 
        NFStringReplace(str, substr, tmp); // "t13.45hasdfasdfs a testasdfasdf" 
        NFStringDestroy(tmp); 
    }

    printf("%s\n", NFStringCString(str)); 

    NFStringDestroy(str); 
    NFStringDestroy(substr); 
}