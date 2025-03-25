#include <stdio.h>
#include <string.h>
#include "hash_table.h"

typedef struct {
    int x;
    double y;
} CustomStruct;

int main() {
    HashTable* hashTable = newHashTable(53, NULL, NULL);

    int intKey = 10;
    double doubleKey = 5.5;
    char* stringKey = "example";
    CustomStruct structKey = {1, 2.5};

    int intValue = 100;
    double doubleValue = 99.99;
    char* stringValue = "Hello, World!";
    CustomStruct structValue = {42, 3.14};

    hashTableInsert(hashTable, &intKey, sizeof(int), &structValue, sizeof(CustomStruct));
    hashTableInsert(hashTable, &doubleKey, sizeof(double), &doubleValue, sizeof(double));
    hashTableInsert(hashTable, stringKey, strlen(stringKey) + 1, stringValue, strlen(stringValue) + 1);
    hashTableInsert(hashTable, &structKey, sizeof(CustomStruct), &intValue, sizeof(int));

    printf("doubleKey: %.2f\n", *(double*)hashTableSearch(hashTable, &doubleKey, sizeof(double)));
    printf("stringKey: %s\n", (char*)hashTableSearch(hashTable, stringKey, strlen(stringKey) + 1));

    CustomStruct* retrievedStruct = hashTableSearch(hashTable, &intKey, sizeof(int));
    if (retrievedStruct) {
        printf("intKey: {x: %d, y: %.2f}\n", retrievedStruct->x, retrievedStruct->y);
    }

    int* retrievedInt = hashTableSearch(hashTable, &structKey, sizeof(CustomStruct));
    if (retrievedInt) {
        printf("structKey: %d\n", *retrievedInt);
    }

    hashTableDelete(hashTable, &doubleKey, sizeof(double));
    printf("doubleKey after deletion: %p\n", hashTableSearch(hashTable, &doubleKey, sizeof(double)));

    deleteHashTable(hashTable);
    return 0;
}
