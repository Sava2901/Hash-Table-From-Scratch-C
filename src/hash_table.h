#ifndef HASH_TABLE_H
#define HASH_TABLE_H


typedef struct Item Item;
typedef struct HashTable HashTable;

struct Item{
    char* key;
    char* value;
};

struct HashTable{
    int size;
    int count;
    Item** items;
};

static Item* newItem(const char* k, const char* v);
static void deleteItem(Item* item);

HashTable* newHashTable();
void deleteHashTable(HashTable* hashTable);


#endif