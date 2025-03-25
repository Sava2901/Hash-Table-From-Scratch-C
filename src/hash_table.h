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

#define hashTableInsert(ht, key, value) \
_hashTableInsert(ht, key, sizeof(*key), value, sizeof(*value))

#define hashTableSearch(ht, key) \
_hashTableSearch(ht, key, sizeof(*key))

#define hashTableDelete(ht, key) \
_hashTableDelete(ht, key, sizeof(*key))

void _hashTableInsert(HashTable* hashTable, const void* key, size_t key_size, const void* value, size_t value_size);
void* _hashTableSearch(const HashTable* hashTable, const void* key, size_t key_size);
void _hashTableDelete(HashTable* hashTable, const void* key, size_t key_size);

#endif
