#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

static unsigned long hashFunction(const char* _key, int size) {
    unsigned long hash = 5381;
    unsigned char *key = (unsigned char*) _key;
    int c;

    while ((c = *key++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % size;
}

static Item* newItem(const char* key, const char* value) {
    Item* item = malloc(sizeof(Item));
    item->key = strdup(key);
    item->value = strdup(value);
    return item;
}

static void deleteItem(Item* item) {
    free(item->key);
    free(item->value);
    free(item);
}

HashTable* newHashTable() {
    HashTable* hashTable = malloc(sizeof(HashTable));
    hashTable->size = 53;
    hashTable->count = 0;
    hashTable->items = calloc((size_t)hashTable->size, sizeof(Item*));
    return hashTable;
}

void deleteHashTable(HashTable* hashTable) {
    for (int i = 0; i < hashTable->size; i++) {
        Item* item = hashTable->items[i];
        if (item != NULL) {
            deleteItem(item);
        }
    }
    free(hashTable->items);
    free(hashTable);
}

void hashTableInsert(HashTable* hashTable, const char* key, const char* value) {
    Item* item = newItem(key, value);

    unsigned long index = hashFunction(key, hashTable->size);

    if (hashTable->items[index] != NULL) {
        deleteItem(hashTable->items[index]);
    }
    hashTable->items[index] = item;
    hashTable->count++;
}

char* hashTableSearch(HashTable* hashTable, const char* key) {
    unsigned long index = hashFunction(key, hashTable->size);

    Item* item = hashTable->items[index];
    if (item != NULL && strcmp(item->key, key) == 0) {
        return item->value;
    }

    return NULL;
}

void hashTableDelete(HashTable* hashTable, const char* key) {
    unsigned long index = hashFunction(key, hashTable->size);

    Item* item = hashTable->items[index];
    if (item != NULL && strcmp(item->key, key) == 0) {
        deleteItem(item);
        hashTable->items[index] = NULL;
        hashTable->count--;
    }
}