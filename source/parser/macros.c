
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

        if (is_variable(args[0]) == -1) {
            fprintf(stderr, "╔ %s: '%s' - what is it? i expect a name variable\n", macros[macro], args[0]);
            return -1;
        }

        if (!((!is_variable(args[1]) || !is_number(args[1]) || !is_string(args[1])) && is_operator(args[1]))) {
            fprintf(stderr, "╔ %s: '%s' - this can't be a variable value\n", macros[macro], args[1]);
            return -1;
        }

        if (is_string(args[1]) == 0 && argc > 2) {
            fprintf(stderr, "╔ %s: '%s' - after variable with string value, i don't expect anything\n", macros[macro], args[1]);
            return -1;
        }

        for (int i = 2; i < argc; ++i) {

            if (i % 2 == 0) {

                if (is_math_operator(args[i]) == -1) {
                    fprintf(stderr, "╔ %s: '%s' - no, i expect a math operator here\n", macros[macro], args[i]);
                    return -1;
                }

            } else {

                if (is_variable(args[i]) == -1 && is_number(args[i]) == -1) {
                    fprintf(stderr, "╔ %s: '%s' - no, i expect variable or number here\n", macros[macro], args[i]);
                    return -1;
                }
            }

        }
    } 

    // if
    else if (macro == 1) {

        if (argc != 1 && argc != 3) {
            fprintf(stderr, "╔ %s: expected one or three arguments\n", macros[macro]);
            return -1;
        }

        for (int i = 1; i < argc; ++i) {

            if (i % 2 != 0) {

                if (is_logic_operator(args[i]) == -1) {
                    fprintf(stderr, "╔ %s: '%s' - no, i expect a logical operator here\n", macros[macro], args[i]);
                    return -1;
                }

            } else {

                if (is_variable(args[i]) == -1 && is_number(args[i]) == -1 && is_string(args[i]) == -1) {
                    fprintf(stderr, "╔ %s: '%s' - no, i expect variable, string or number here\n", macros[macro], args[i]);
                    return -1;
                }
            }

        }

    }

    // ifndef
    else if (macro == 2) {

        if (argc == 0) {
            fprintf(stderr, "╔ %s: expected one variable\n", macros[macro]);
            return -1;
        }

        if (argc > 1) {
            fprintf(stderr, "╔ %s: '%s' - what? i expected only one variable. delete it\n", macros[macro], args[1]);
            return -1;
        }

        if (is_variable(args[0]) == -1) {
            fprintf(stderr, "╔ %s: '%s' - i expect variable here\n", macros[macro], args[0]);
            return -1;
        }

    }

    // else
    else if (macro == 3) {

        if (argc > 0) {
            fprintf(stderr, "╔ %s: '%s' - do you joke? this is 'else' branch. delete it\n", macros[macro], args[1]);
            return -1;
        }

    }

    // endif
    else if (macro == 4) {

        if (argc > 0) {
            fprintf(stderr, "╔ %s: '%s' - what is it? i don't expect anything here\n", macros[macro], args[0]);
            return -1;
        }
    }

    // undef
    else if (macro == 5) {

        if (argc == 0) {
            fprintf(stderr, "╔ %s: expected one variable here\n", macros[macro]);
            return -1;
        }

        if (is_variable(args[0]) == -1) {
            fprintf(stderr, "╔ %s: '%s' - this is not variable\n", macros[macro], args[0]);
            return -1;
        }

        if (argc > 1) {
            fprintf(stderr, "╔ %s: '%s' - what it is? i expected only one variable here\n", macros[macro], args[1]);
            return -1;
        }
    }

    return 0;
}


int is_string(char* value) {

    int i = 0;

    if (value[i] != '"')
        return -1;

    while (value[i] != 0) i++;

    return (value[i - 1] != '"' ? -1 : 0);
}

int is_operator(char* value) {

    for (int i = 0; i < OPERATOR_N; ++i) {

        if (strcmp(value, operators[i]) == 0)
            return i;
    }

    return -1;
}

int is_math_operator(char* value) {

    for (int i = 0; i < MATH_OPERATOR_N; ++i) {

        if (strcmp(value, math_operators[i]) == 0)
            return i;
    }

    return -1;
}

int is_logic_operator(char* value) {

    for (int i = 0; i < LOGIC_OPERATOR_N; ++i) {

        if (strcmp(value, logic_operators[i]) == 0)
            return MATH_OPERATOR_N + i - 1;
    }

    return -1;
}

int is_number(char* value) {

    int i = 0;

    while (value[i] != 0) {

        if (isalpha(value[i]) || !isdigit(value[i])) {
            return -1;
        }

        i++;
    }

    return 0;
}

int is_variable(char* value) {

    if (isalpha(value[0]) && is_operator(value) == -1 && value[0] != '"' && value[0] != '#') {
        return 0;
    }

    return -1;
}
