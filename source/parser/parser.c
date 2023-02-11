
#include "parser.h"

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

short check_syntax() {

    char** ptr = files;
    int k = count;

    FILE* fp;

    while (--k >= 0) {
        fp = fopen(*(ptr++), "r");

        if (fp == NULL) {
            printf("File with path '%s' is not found\n", files[k]);
            return 1;
        }

        int status = is_valid_file(fp);
        fclose(fp);

        if (status != 0) return status;
    }

    return 0;
}

short is_valid_file(FILE* fp) {

    int i = 0;
    char** args;

    int k = 0;

    while ((args = parseLine(fp)) != NULL) {

        printf("-- line %d\n", ++k);

        i = 0;

        while (args[i] != NULL && args[i] != '\0') {
            printf(" arg %d: %s|\n", i, args[i]);
            ++i;
        }

        printf("\n");
    }

    return 0;
}

char** parseLine(FILE* fp) {
    
    char* line = malloc(MAX_LINE_LEN * sizeof(char));
    
    if (fgets(line, MAX_LINE_LEN, fp) == NULL)
        return NULL;

    // printf("%s", line);

    // COUTN ARGUMENTS

    int i = 0, k = 0, j = 0;

    char** args = malloc(MAX_ARG_N * sizeof(char*));

    while(k < MAX_ARG_N)
        args[k++] = NULL;

    k = 0;

    while (i < strlen(line) && line[i] == ' ') i++;

    while (line[i] != '\0' && i < MAX_LINE_LEN && k < MAX_ARG_LEN) {

        if (line[i] == ' ') {
            if (j > 0)
                args[k][j] = '\0';
            j = 0; k++; i++;
            continue;
        }

        if (args[k] == NULL) {
            args[k] = malloc(MAX_ARG_LEN * sizeof(char));
            printf("%d\n", k);
        }

        // printf("k = %d, j = %d, i = %d\n", k, j, i);

        args[k][j] = line[i];

        // printf("what\n");

        j++; i++;
    }

    // while (line[i] != '\0' && line[i] != 10 && i < MAX_LINE_LEN) {

    //     if (line[i] == ' ') {
    //         args[k][j] = '\0';
    //         j = 0; k++; i++;
    //         continue;
    //     }

    //     if (args[k] == NULL) {
    //         args[k] = malloc(MAX_ARG_LEN * sizeof(char) + 1);
    //     }

    //     // printf("%c: k = %d, j = %d\n", line[i], k, j);

    //     args[k][j++] = line[i++];
    // }

    return args;
}

void free_parser() {

    for (int i = 0; i < count; ++i)
        free(files[i]);

    free(files);
}
