#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

static unsigned long defaultHashFunction(const void* key, size_t key_size, int size) {
    const unsigned char* data = key;
    unsigned long hash = 5381;
    for (size_t i = 0; i < key_size; i++) {
        hash = (hash << 5) + hash + data[i];
    }
    return hash % size;
}

static int defaultKeyCompare(const void* key1, const void* key2, size_t key_size) {
    return memcmp(key1, key2, key_size);
}

static Item* newItem(const void* key, size_t key_size, const void* value, size_t value_size) {
    Item* item = malloc(sizeof(Item));
    item->key = malloc(key_size);
    item->value = malloc(value_size);
    memcpy(item->key, key, key_size);
    memcpy(item->value, value, value_size);
    item->key_size = key_size;
    item->value_size = value_size;
    item->next = NULL;
    return item;
}

static void deleteItem(Item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

HashTable* newHashTable(int size, HashFunction hash_function, KeyCompareFunction key_compare) {
    HashTable* hashTable = malloc(sizeof(HashTable));
    hashTable->size = size;
    hashTable->count = 0;
    hashTable->items = calloc(size, sizeof(Item*));
    hashTable->hash_function = hash_function ? hash_function : defaultHashFunction;
    hashTable->key_compare = key_compare ? key_compare : defaultKeyCompare;
    return hashTable;
}

void deleteHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        Item* current = hashTable->items[i];
        while (current != NULL) {
            Item* temp = current;
            current = current->next;
            deleteItem(temp);
        }
    }
    free(hashTable->items);
    free(hashTable);
}

void hashTableInsert(HashTable* hashTable, const void* key, size_t key_size, const void* value, size_t value_size) {
    unsigned long index = hashTable->hash_function(key, key_size, hashTable->size);
    Item* current = hashTable->items[index];

    while (current != NULL) {
        if (hashTable->key_compare(current->key, key, key_size) == 0) {
            free(current->value);
            current->value = malloc(value_size);
            memcpy(current->value, value, value_size);
            current->value_size = value_size;
            return;
        }
        current = current->next;
    }

    Item* new_item = newItem(key, key_size, value, value_size);
    new_item->next = hashTable->items[index];
    hashTable->items[index] = new_item;
    hashTable->count++;
}

void* hashTableSearch(const HashTable* hashTable, const void* key, size_t key_size) {
    unsigned long index = hashTable->hash_function(key, key_size, hashTable->size);
    Item* current = hashTable->items[index];

    while (current != NULL) {
        if (hashTable->key_compare(current->key, key, key_size) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void hashTableDelete(HashTable* hashTable, const void* key, size_t key_size) {
    unsigned long index = hashTable->hash_function(key, key_size, hashTable->size);
    Item* current = hashTable->items[index];
    Item* prev = NULL;

    while (current != NULL) {
        if (hashTable->key_compare(current->key, key, key_size) == 0) {
            if (prev == NULL) {
                hashTable->items[index] = current->next;
            } else {
                prev->next = current->next;
            }
            deleteItem(current);
            hashTable->count--;
            return;
        }
        prev = current;
        current = current->next;
    }
}
