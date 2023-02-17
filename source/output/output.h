
#include "../table/table.h"

typedef void (do_output)(void*, const char*, const char*);

void print_table(Table* table, do_output* func);
