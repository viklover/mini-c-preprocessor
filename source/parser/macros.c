
#include "macros.h"

int macro_is_exists(char* input) {
    
    for (int i = 0; i < MACRO_N; ++i) {

        if (strcmp(macros[i], input) == 0) {
            return i;
        }
    }

    return -1;
}

int is_valid_macro(int macro, int argc, char** args) {

    //define
    if (macro == 0) {

        if (argc < 2) {
            fprintf(stderr, "╔ %s: expected at least two arguments\n", macros[macro]);
            return -1;
        }

    }

    return 0;
}
