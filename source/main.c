
#include <stdio.h>

#include "table/table.h"
#include "parser/parser.h"

int main(int argc, char *argv[]) {

    while (--argc > 0) {

        if (!file_is_exists(argv[argc])) {
            fprintf(stderr, "File with path '%s' is not exists\n", argv[argc]);
            return 1;
        }

        add_file(argv[argc]);
    }

    short file, status;

    if ((file = check_syntax()) != 0) {
        fprintf(stderr, "╚══ Syntax error in file '%s'\n", get_filename(file - 1));
        return 1;
    }

    Table* table = create_table();

    if ((status = run(table)) != 0) {
        fprintf(stderr, "╚══ Runtime exception\n");
        return 1;
    }

    // print(table);

    return 0;
}
