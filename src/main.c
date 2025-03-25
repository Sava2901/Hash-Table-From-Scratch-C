#include <stdio.h>
#include "hash_table.h"

typedef struct {
    int id;
    double score;
    char name[20];
} Student;

int main() {
    HashTable* hashTable = newHashTable(53, NULL, NULL);

    int intKey = 42;
    char stringKey = "studentA";

    Student studentValue = {101, 95.5, "Alice"};
    int intValue = 999;

    hashTableInsert(hashTable, &intKey, &studentValue);
    hashTableInsert(hashTable, &stringKey, &intValue);

    Student* retrievedStudent = hashTableSearch(hashTable, &intKey);
    if (retrievedStudent) {
        printf("Student (ID: %d, Score: %.1f, Name: %s)\n",
               retrievedStudent->id, retrievedStudent->score, retrievedStudent->name);
    }

    int* retrievedInt = hashTableSearch(hashTable, &stringKey);
    if (retrievedInt) {
        printf("Retrieved int for key 'studentA': %d\n", *retrievedInt);
    }

    deleteHashTable(hashTable);

    return 0;
}
