
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

/*

while (i < MAX_ARG_LEN && line[i] != 0) {

    if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

        if (line[i] == '"')
            in_quotes = (in_quotes ? 0 : 1);

        if (!is_argument) {
            args[l] = malloc(MAX_ARG_LEN * sizeof(char));
            is_argument = 1;
            j = i;
        }
    }
    else if (is_argument && !in_quotes) {
        is_argument = 0;
        k = i;
        
        strncpy(args[l], line + j, k - j);
        args[l][k - j] = '\0';

        printf("arg: %s", args[l]);

        l++;
    }
    
    i++;
}
*/
