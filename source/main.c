
#include <stdio.h>

#include "table/table.h"
#include "parser/parser.h"

int main(int argc, char *argv[]) {

    while (--argc > 0)
        add_file(*++argv);

    Table* table = create_table();

    short s = check_syntax();

    if (s != 0) {

        if (s == -1)
            fprintf(stderr, "One of file has invalid syntax");

        return 1;
    }

    free_table(table);
    free_parser();

    return 0;
}
