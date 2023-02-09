
#include <stddef.h>

#include "table.h"

unsigned long hash(char* str) {

    unsigned long i = 0;
    
    for (int j = 0; str[j]; j++) {
        i += str[j];
    }
    
    return i % TABLE_CAPACITY;
}

Table* create_table() {

    Table* table = (Table*) malloc(sizeof(Table));

    table->count = 0;
    table->items = (Item**) calloc(TABLE_CAPACITY, sizeof(Item*));
    
    for (int i = 0; i < TABLE_CAPACITY; i++) {
        table->items[i] = NULL;
    }
    
    return table;
}

Item* create_item(char* key, char* value) {

    Item* item = (Item*) malloc(sizeof(Item));
    
    item->next = NULL;

    item->key = (char*) malloc(strlen(key) + 1);
    item->value = (char*) malloc(strlen(value) + 1);

    strcpy(item->key, key);
    strcpy(item->value, value);

    return item;
}

char* get(Table* table, char* key) {

    unsigned index = hash(key);

    Item* item = table->items[index];

    if (item != NULL) {

        while (item->next != NULL) {

            if (strcmp(item->key, key) == 0) {
                return item->value;
            }

            item = item->next;
        }

        return item->value;
    }

    return NULL;
}

void put(Table* table, char* key, char* value) {

    unsigned index = hash(key);

    if (table->items[index] != NULL) {

        if (strcmp(table->items[index]->key, key) == 0) {
            table->items[index]->value = value;
        } else {
            Item* item = create_item(key, value);
            connect(table->items[index], item);   
        }

        return;
    }
    
    table->items[index] = create_item(key, value);
}

void connect(Item* chain, Item* item) {

    if (chain->next == NULL) {
        chain->next = item;
        return;
    }

    Item* elem;

    while (chain->next != NULL) {
        elem = chain->next;
    }

    elem->next = item;
}


void free_item(Item* item) {

    if (item != NULL) {
        return;
    }

    free_item(item->next);
    
    if (item->next != NULL)
        free(item->next);

    free(item->key);
    free(item->value);
}

void free_table(Table* table) {

    for (int i = 0; i < table->count; ++i) {
        free_item(table->items[i]);
    }

    free(table);
}
