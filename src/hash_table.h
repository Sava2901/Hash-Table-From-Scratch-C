#ifndef HASH_TABLE_H
#define HASH_TABLE_H

typedef struct Item Item;
typedef struct HashTable HashTable;

struct Item {
    char* key;
    char* value;
    Item* next;
};

struct HashTable {
    int size;
    int count;
    Item** items;
};

static Item* newItem(const char* key, const char* value);
static void deleteItem(Item* item);

HashTable* newHashTable();
void deleteHashTable(HashTable* hashTable);

void hashTableInsert(HashTable* hashTable, const char* key, const char* value);
char* hashTableSearch(HashTable* hashTable, const char* key);
void hashTableDelete(HashTable* hashTable, const char* key);

#endif
