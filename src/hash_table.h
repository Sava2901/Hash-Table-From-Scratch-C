#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct Item Item;
typedef struct HashTable HashTable;
typedef unsigned long (*HashFunction)(const void* key, size_t key_size, int size);
typedef int (*KeyCompareFunction)(const void* key1, const void* key2, size_t key_size);

struct Item {
    void* key;
    void* value;
    size_t key_size;
    size_t value_size;
    Item* next;
};

struct HashTable {
    int size;
    int count;
    Item** items;
    HashFunction hash_function;
    KeyCompareFunction key_compare;
};

HashTable* newHashTable(int size, HashFunction hash_function, KeyCompareFunction key_compare);
void deleteHashTable(HashTable* hashTable);

void hashTableInsert(HashTable* hashTable, const void* key, size_t key_size, const void* value, size_t value_size);
void* hashTableSearch(const HashTable* hashTable, const void* key, size_t key_size);
void hashTableDelete(HashTable* hashTable, const void* key, size_t key_size);

#endif
