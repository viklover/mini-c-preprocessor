
#include <stdio.h>

#include "table/table.h"
#include "parser/parser.h"

int main(int argc, char *argv[]) {

    int files_exist, file, status;

    if ((files_exist = add_files(argc, argv) != 0))
        return files_exist;

    if ((file = check_syntax()) != 0) {
        fprintf(stderr, "╚══ Syntax error in file '%s'\n", get_filename(file - 1));
        return 1;
    }

    Table* table = create_table();

    if ((status = run(table)) != 0) {
        fprintf(stderr, "╚══ Runtime exception\n");
        return 1;
    }

    print(table);

    return 0;
}
