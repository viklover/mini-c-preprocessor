
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ARG_LEN 128
#define MAX_ARG_N 64
#define MAX_LINE_LEN 256

static char** files;
static unsigned int count = 0;

void add_file(char* path);
short check_syntax();
short is_valid_file(FILE* fp);

char** parseLine();

void free_parser();
