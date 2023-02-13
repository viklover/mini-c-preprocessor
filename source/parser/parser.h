#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../table/table.h"
#include "macros.h"

#define MAX_ARG_LEN 128
#define MAX_ARG_N 64
#define MAX_LINE_LEN 256

static char** files;
static unsigned int count = 0;

int file_is_exists(char* path);

void add_file(char* path);
char* get_filename(int index);

short check_syntax();
short check_syntax_file(FILE* fp);

short run(Table* table);

void print(Table* table);

int parse_macro(char* line, int* i, int* j);
int parsing_args(char** args, char* line, int* i, int* j);

void free_parser();
