
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int parse_line_args(FILE* fp, char** args);

void free_parser();
