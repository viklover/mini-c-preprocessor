
#include <string.h>

#define MACRO_LEN 8
#define MACRO_N 6

typedef struct Instruction Instruction;

struct Instruction {
    char* macros;
    char** arguments;
};

static char* macros[] = {"define", "if", "ifndef", "else", "endif", "undef"};
static char* operators[] = {"+", "-", "*", "=="};

int macros_is_exists(char* macros);