
#include <ctype.h>
#include <stdio.h>
#include <string.h>

#define MACRO_LEN 8
#define MACRO_N 6

#define OPERATOR_N 6
#define MATH_OPERATOR_N 3
#define LOGIC_OPERATOR_N 1

typedef struct Instruction Instruction;

struct Instruction {
    char* macros;
    char** arguments;
};

static char* macros[] = {"define", "if", "ifndef", "else", "endif", "undef"};
static char* operators[] = {"+", "-", "*", "=="};
static char* math_operators[] = {"+", "-", "*"};
static char* logic_operators[] = {"=="};

int macro_is_exists(char* input);
int is_valid_macro(int macro, int argc, char** args);

int is_string(char* value);
int is_operator(char* value);
int is_math_operator(char* value);
int is_logic_operator(char* value);
int is_number(char* value);
int is_variable(char* value);
