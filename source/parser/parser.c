
#include "parser.h"
#include "macros.h"

int file_is_exists(char* path) {
    FILE* fp = fopen(path, "r");
    int exists = fp == NULL ? 0 : 1;
    if (exists) fclose(fp);
    return exists;
}

void add_file(char* path) {

    char** new_files = malloc(++count * sizeof(char*));

    int i = -1;

    while (++i < count - 1) {
        new_files[i] = (char*) malloc(sizeof(char) * (strlen(files[i]) + 1));
        strcpy(new_files[i], files[i]);
    }

    new_files[count - 1] = (char*) malloc(sizeof(char) * (strlen(path) + 1));
    strcpy(new_files[count - 1], path);

    files = new_files;
}

char* get_filename(int index) {
    return files[index];
}


short check_syntax() {

    char** ptr = files;
    int k = count;

    FILE* fp;

    while (--k >= 0) {
        fp = fopen(*(ptr++), "r");

        int status = check_syntax_file(fp);
        fclose(fp);

        if (status != 0) 
            return count - k;
    }

    return 0;
}

short check_syntax_file(FILE* fp) {

    int i, j, k;

    int current_line = 0;
    char* line = malloc(MAX_LINE_LEN * sizeof(char));

    while (fgets(line, MAX_LINE_LEN, fp) != 0 && ++current_line) {
        
        i = 0; j = 0; k = 0;

        while (i < MAX_LINE_LEN && line[i] != '#' && line[i] != 0) 
            i++;

        j = i;

        while (i < MAX_LINE_LEN && line[i] != ' ' && line[i] != '\n' && line[i] != 0)
            i++;
        
        k = i;

        if (j - k == 0)
            continue;

        char* macros = malloc(MACRO_LEN * sizeof(char));
        
        strncpy(macros, line + j + 1, k - j - 1);

        macros[k - j - 1] = '\0';

        if (macros_is_exists(macros) == -1) {
            fprintf(stderr, "%d line: macros '%s' is not exists\n", current_line, macros);
            return -1;
        }
    }

    // // COUTN ARGUMENTS WITH PUTTING ARGUMENTS BOUND INDEXES
    // int args_count = 0; 
    // int is_argument = 0;
    // int in_quotes = 0;
    // int index = 0;

    // i = 0; j = 0;

    // while (i < MAX_LINE_LEN && line[i] != 0) {
        
    //     if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

    //         if (line[i] == '"') {
    //             in_quotes = (in_quotes ? 0 : 1);
    //         }

    //         if (!is_argument) {
    //             words[index][0] = i;
    //             is_argument = 1;
    //             args_count++;
    //         }
    //     } 
    //     else if (is_argument && !in_quotes) {
    //         words[index][1] = i;
    //         index++;
    //         is_argument = 0;
    //     }

    //     ++i;
    // }

    // if (is_argument && line[i] == 0 && !in_quotes) {
    //     words[index][1] = i;
    // }

    // if (!args_count)
    //     return 1;

    // if (in_quotes)
    //     return 2; 

    // for (i = 0; i < MAX_ARG_N && words[i][0] != -1; ++i)
    //     printf("argument: %d:%d\n", words[i][0], words[i][1]);

    return 0;
}


int parse_line_args(FILE* fp, char** args) {

    char* line = malloc(MAX_LINE_LEN * sizeof(char));
    
    if (fgets(line, MAX_LINE_LEN, fp) == NULL)
        return -1;

    // printf("%s", line);

    // PREPARE WORDS ARRAY FOR INDEXES STORING
    int** words = malloc(MAX_ARG_N * sizeof(int*));

    int i, j;

    for (i = 0; i < MAX_ARG_N; ++i) {
        words[i] = malloc(2 * sizeof(int));

        for (j = 0; j < 2; ++j)
            words[i][j] = -1;
    }

    // SKIP SPACES OR TABS IN BEGGINING OF LINE
    while (i < MAX_LINE_LEN && line[i] != '#') 
        i++;

    // COUTN ARGUMENTS WITH PUTTING ARGUMENTS BOUND INDEXES
    int args_count = 0; 
    int is_argument = 0;
    int in_quotes = 0;
    int index = 0;

    i = 0; j = 0;

    while (i < MAX_LINE_LEN && line[i] != 0) {
        
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n') {

            if (line[i] == '"') {
                in_quotes = (in_quotes ? 0 : 1);
            }

            if (!is_argument) {
                words[index][0] = i;
                is_argument = 1;
                args_count++;
            }
        } 
        else if (is_argument && !in_quotes) {
            words[index][1] = i;
            index++;
            is_argument = 0;
        }

        ++i;
    }

    if (is_argument && line[i] == 0 && !in_quotes) {
        words[index][1] = i;
    }

    if (!args_count)
        return 1;

    if (in_quotes)
        return 2; 

    // for (i = 0; i < MAX_ARG_N && words[i][0] != -1; ++i)
    //     printf("argument: %d:%d\n", words[i][0], words[i][1]);

    return 0;
}

void free_parser() {

    for (int i = 0; i < count; ++i)
        free(files[i]);

    free(files);
}
