#include <stdlib.h>
#include <string.h>

#include "hash_table.h"


//Create item
static Item* newItem(const char* n_key, const char* n_value) {
    Item* item = malloc(sizeof(Item));

    item->key = strdup(n_key);
    item->value = strdup(n_value);

    return item;
}

//Delete item
static void deleteItem(Item* item) {
    free(item->key);
    free(item->value);
    free(item);
}


//Create hash table
HashTable* newHashTable() {
    HashTable* hashTable = malloc(sizeof(HashTable));

    hashTable->size = 53;
    hashTable->count = 0;
    hashTable->items = calloc((size_t)hashTable->size, sizeof(Item*));

    return hashTable;
}


//Delete hash table
void deleteHashTable(HashTable* hashTable) {
    for(int i = 0; i < hashTable->size; i++) {
        Item* hashTableItem = hashTable->items[i];
        if(hashTableItem != NULL) {
            deleteItem(hashTableItem);
        }
    }
    free(hashTable->items);
    free(hashTable);
}