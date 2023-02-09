
#include <stdio.h>

#include "table/table.h"

int main(char *argv[]) {

    Table* table = create_table();

    // In ASCII coding: "Hel" and "Cau" have one eqaul hash
    put(table, "A", "B");
    put(table, "Hel", "world");
    put(table, "Cau", "world2");

    printf("%s\n", get(table, "A"));
    printf("%s\n", get(table, "Hel"));
    printf("%s\n", get(table, "Cau"));

    free_table(table);

    return 0;
}
