
#include <stdio.h>

#include "table/table.h"
#include "parser/parser.h"
#include "output/output.h"

void print_console(void *ctx, const char *macro_name, const char *macro_val) {
    printf("# %s\n%s\n\n", macro_name, macro_val);
}

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

    print_table(table, print_console);

    return 0;
}
