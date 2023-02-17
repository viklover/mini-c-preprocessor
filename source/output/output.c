
#include "output.h"

void print_table(Table* table, do_output* func) {

    char** keys_array = keys(table);

    for (int i = 0; i < table->count; ++i) {
        (*func)(0, keys_array[i], get(table, keys_array[i]));
    }
}
