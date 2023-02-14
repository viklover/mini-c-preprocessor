#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_CAPACITY 1000

typedef struct HashTable Table;
typedef struct TableItem Item;

struct TableItem {
    char* key;
    char* value;
    Item* next;
};

struct HashTable {
    Item** items;
    unsigned count;
};


unsigned long hash(char* str);

Table* create_table();
Item* create_item(char* key, char* value);

char** keys(Table* table);
int contains_key(Table* table, char* key);

char* get(Table* table, char* key);
void delete(Table* table, char* key);

void put(Table* table, char* key, char* value);
void connect(Item* chain, Item* item);

void print(Table* table);

void free_item(Item* item);
void free_table(Table* table);
