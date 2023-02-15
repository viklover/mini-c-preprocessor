#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"
#include "../table/table.h"

#include "util.h"

#define MACRO_LEN 8
#define MACRO_N 7

#define OPERATOR_N 6
#define MATH_OPERATOR_N 3
#define LOGIC_OPERATOR_N 1

#define STACK_LEN 1024
#define STACK_VALUE 256

#define INSTRUCTIONS_N 1024

typedef struct Instruction Instruction;

struct Instruction {
    int macros;
    char** args;
    int argc;
};

Instruction* create_instruction(int macro, int argc, char** args);

short execute(Table* table, Instruction* instruction, int* level);

int sum(char* result, char* value1, char* value2);
int minus(char* result, char* value1, char* value2);
int multiply(char* result, char* value1, char* value2);

int get_value(Instruction* instruction, int arg_index, char* dest, Table* table);

int operate(char* operator, char* result, char* value1, char* value2);

static char* macros[] = {"define", "if", "ifndef", "else", "endif", "undef", "elif"};
static char* operators[] = {"+", "-", "*", "=="};
static char* math_operators[] = {"+", "-", "*"};
static char* logic_operators[] = {"=="};

int macro_index(char* input);
int is_valid_macro(int macro, int argc, char** args);

int is_string(char* value);
int is_operator(char* value);
int is_math_operator(char* value);
int is_logic_operator(char* value);
int is_number(char* value);
int is_variable(char* value);