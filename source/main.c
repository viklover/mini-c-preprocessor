
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

    short file;

    if ((file = check_syntax()) != 0) {
        fprintf(stderr, "╚══ Syntax error in file '%s'\n", get_filename(file - 1));
        return 1;
    }

    return 0;
}
