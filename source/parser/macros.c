
#include "macros.h"

Instruction* parseWords(char** words) {

}

int macros_is_exists(char* input) {
    
    for (int i = 0; i < MACRO_N; ++i) {

        if (strcmp(macros[i], input) == 0) {
            return 0;
        }
    }

    return -1;
}
