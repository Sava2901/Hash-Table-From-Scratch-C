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

void hashTableInsert(HashTable* hashTable, const char* key, const char* value) {
    unsigned long index = hashFunction(key, hashTable->size);
    Item* current = hashTable->items[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = strdup(value);
            return;
        }
        current = current->next;
    }

    Item* new_item = newItem(key, value);
    new_item->next = hashTable->items[index];
    hashTable->items[index] = new_item;
    hashTable->count++;
}

char* hashTableSearch(HashTable* hashTable, const char* key) {
    unsigned long index = hashFunction(key, hashTable->size);
    Item* current = hashTable->items[index];

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            return current->value;
        }
        current = current->next;
    }

    return NULL;
}

void hashTableDelete(HashTable* hashTable, const char* key) {
    unsigned long index = hashFunction(key, hashTable->size);
    Item* current = hashTable->items[index];
    Item* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
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