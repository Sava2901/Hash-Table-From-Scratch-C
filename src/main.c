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

    hashTableInsert(hashTable, "city", "Neverland");
    printf("Updated city: %s\n", hashTableSearch(hashTable, "city"));

    hashTableDelete(hashTable, "age");
    printf("age after deletion: %s\n", hashTableSearch(hashTable, "age"));

    hashTableInsert(hashTable, "key1", "value1");
    hashTableInsert(hashTable, "key2", "value2");
    hashTableInsert(hashTable, "key3", "value3");

    printf("key1: %s\n", hashTableSearch(hashTable, "key1"));
    printf("key2: %s\n", hashTableSearch(hashTable, "key2"));
    printf("key3: %s\n", hashTableSearch(hashTable, "key3"));

    hashTableDelete(hashTable, "key2");
    printf("key2 after deletion: %s\n", hashTableSearch(hashTable, "key2"));

    printf("key1: %s\n", hashTableSearch(hashTable, "key1"));
    printf("key3: %s\n", hashTableSearch(hashTable, "key3"));

    deleteHashTable(hashTable);

    printf("All tests completed successfully.\n");
    return 0;
}
