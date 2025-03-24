#include <stdio.h>
#include "hash_table.h"

int main() {
    HashTable* hashTable = newHashTable();

    hashTableInsert(hashTable, "name", "Alice");
    hashTableInsert(hashTable, "age", "25");
    hashTableInsert(hashTable, "city", "Wonderland");

    printf("name: %s\n", hashTableSearch(hashTable, "name"));
    printf("age: %s\n", hashTableSearch(hashTable, "age"));
    printf("city: %s\n", hashTableSearch(hashTable, "city"));
    printf("country: %s\n", hashTableSearch(hashTable, "country"));

    hashTableDelete(hashTable, "age");
    printf("age after deletion: %s\n", hashTableSearch(hashTable, "age"));

    deleteHashTable(hashTable);

    return 0;
}