
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

int contains_key(Table* table, char* key) {

    char** keys_array = keys(table);

    for (int i = 0; i < table->count; ++i) {
        if (strcmp(keys_array[i], key) == 0)
            return 0;
    }

    return -1;
}

char** keys(Table* table) {

    char** array = malloc(table->count * sizeof(char*));

    int k = 0;

    for (int i = 0; i < TABLE_CAPACITY; ++i) {
        
        if (table->items[i] == 0)
            continue;

        array[k] = malloc(strlen(table->items[i]->key)*sizeof(char));
        strcpy(array[k], table->items[i]->key);
        k++;

        Item* item = table->items[i]->next;

        while (item != 0) {

            array[k] = malloc(strlen(item->key)*sizeof(char));
            strcpy(array[k], item->key);
            k++;

            item = item->next;
        }
    }

    return array;
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

            table->count++;
        }

        return;
    }
    
    table->items[index] = create_item(key, value);
    table->count++;
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

void delete(Table* table, char* key) {

    unsigned index = hash(key);
    
    Item* item = table->items[index];
    
    if (item == 0)
        return;

    if (item->next == 0) {
        table->items[index] = NULL;
        free_item(item);
        table->count--;
        return;
    }

    Item* current = item->next;
    Item* prev = 0;

    while (current != 0) {
        
        if (strcmp(current->key, key) == 0) {

            if (prev == 0) {
                table->items[index]->next = current->next;
                free(current);
            } else if (current->next != 0) {
                prev->next = current->next;
                free(item);
            } else {
                prev->next = 0;
                free(item);
            }

            table->count--;
 
            return;
        }

        prev = current;
        current = current->next;
    }
}

void print(Table* table) {

    char** keys_array = keys(table);

    for (int i = 0; i < table->count; ++i) {
        printf("# %s\n", keys_array[i]);
        printf("%s\n", get(table, keys_array[i]));

        if (i + 1 < table->count) 
            printf("\n");
    }
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
