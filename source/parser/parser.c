
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
        
        // FINDING MACRO AND EXSITING CHECKING
        i = 0; j = 0; k = 0;

        while (i < MAX_LINE_LEN && line[i] != '#' && line[i] != 0) 
            i++;

        j = i;

        while (i < MAX_LINE_LEN && line[i] != ' ' && line[i] != '\n' && line[i] != 0)
            i++;
        
        k = i;

        if (j - k == 0)
            continue;

        char* macro = malloc(MACRO_LEN * sizeof(char));
        
        strncpy(macro, line + j + 1, k - j - 1);

        macro[k - j - 1] = '\0';

        int current_macro = -1;

        if ((current_macro = macro_index(macro)) == -1) {
            fprintf(stderr, "╔ %d line: macro '%s' is not exists\n", current_line, macro);
            return -1;
        }

        // PARSING ARGUMENTS AND VALIDATING
        char** args = malloc(MAX_ARG_N * sizeof(char*));

        for (int p = 0; p < MAX_ARG_N; ++p)
            args[p] = 0;

        int in_quotes;
        int l = 0;

        while (i < MAX_ARG_LEN && line[i] != 0) {

            in_quotes = 0;
            j = 0; k = 0;

            while (line[i] == ' ' || line[i] == '\t')
                ++i;

            j = i;

            if (line[i] == '"') {

                ++i;

                while (line[i] != '"' && line[i] != 0 && line[i] < MAX_ARG_LEN)
                    ++i;

                if (line[i] == 0) {
                    fprintf(stderr, "╔ %d line: quotes are not closed\n", current_line);
                    return -1;
                }
                
                ++i;
            } 
            else {

                while (line[i] != ' ' && line[i] != 0 && line[i] < MAX_ARG_LEN)
                    ++i;
            }

            k = i;

            if ((k - j == 1 && (line[j] == ' ' || line[j] == 10)) || k == j)
                continue;

            args[l] = malloc((k - j) * sizeof(char) + 1);
            strncpy(args[l], line + j, k - j);

            if (line[i] == 0) {

                if (line[i - 1] == 10)
                    args[l][k - j - 1] = '\0';
                else
                    args[l][k - j - 2] = '\0';
            }
            else {
                args[l][k - j] = '\0';
            }

            // for (int m = 0; m < i + 1; ++m)
            //     printf("|%d|", line[m]);

            // printf("\n");

            l++;
        }

        if (is_valid_macro(current_macro, l, args) != 0) {
            fprintf(stderr, "╠ %d line: macro has invalid arguments\n", current_line);
            return -1;
        }
    }

    return 0;
}


short run(Table* table) {

    Instruction** instructions = malloc(INSTRUCTIONS_N * sizeof(Instruction*));
    
    int instructions_num = 0;
    
    for (int i = 0; i < INSTRUCTIONS_N; ++i)
        instructions[i] = NULL;


    char** ptr = files;
    int k = count;

    FILE* fp;

    while (--k >= 0) {
        
        fp = fopen(*(ptr++), "r");

        int i, j, k;

        int current_line = 0;
        char* line = malloc(MAX_LINE_LEN * sizeof(char));

        while (fgets(line, MAX_LINE_LEN, fp) != 0 && ++current_line) {
            
            i = 0; j = 0;

            // PARSING MACRO
            short macro;

            if ((macro = parse_macro(line, &i, &j)) == -1) {
                continue;
            }

            // PARSING ARGUMENTS
            char** args = malloc(MAX_ARG_N * sizeof(char*));
            int argc;

            if ((argc = parsing_args(args, line, &i, &j)) == -1) {
                continue;
            }

            Instruction* instruction = create_instruction(macro, argc, args);
            instructions[instructions_num++] = instruction;
        }

        fclose(fp);
    }

    int level = 0;

    for (int i = 0, status; i < instructions_num; ++i) {
        
        if ((status = execute(table, instructions[i], &level)) == -1) {
            fprintf(stderr, "╠ '%s' macros\n", macros[instructions[i]->macros]);
            return -1;
        }
    }

    return 0;
}


int parse_macro(char* line, int* i, int* j) {

    int k = 0;

    while (*i < MAX_LINE_LEN && line[*i] != '#' && line[*i] != 0) 
        (*i)++;

    *j = *i;

    while (*i < MAX_LINE_LEN && line[*i] != ' ' && line[*i] != '\n' && line[*i] != 0)
        (*i)++;
    
    k = *i;

    if ((*j - k) == 0)
        return -1;

    char* macro = malloc(MACRO_LEN * sizeof(char));
    strncpy(macro, line + *j + 1, k - *j - 1);

    macro[k - *j - 1] = '\0';

    return macro_index(macro);
}

int parsing_args(char** args, char* line, int* i, int* j) {

    for (int p = 0; p < MAX_ARG_N; ++p)
        args[p] = 0;

    int in_quotes;
    int l = 0, k = 0;

    while (*i < MAX_ARG_LEN && line[*i] != 0) {

        in_quotes = 0;
        k = 0;
        *j = 0; 

        while (line[*i] == ' ' || line[*i] == '\t')
            ++(*i);

        *j = *i;

        if (line[*i] == '"') {

            ++(*i);

            while (line[*i] != '"' && line[*i] != 0 && line[*i] < MAX_ARG_LEN)
                ++(*i);
            
            ++(*i);
        } 
        else {

            while (line[*i] != ' ' && line[*i] != 0 && line[*i] < MAX_ARG_LEN)
                ++(*i);
        }

        k = *i;

        if ((k - *j == 1 && (line[*j] == ' ' || line[*j] == 10)) || k == *j)
            continue;

        args[l] = malloc((k - *j) * sizeof(char) + 1);
        strncpy(args[l], line + *j, k - *j);

        if (line[*i] == 0) {

            if (line[*i - 1] == 10)
                args[l][k - *j - 1] = '\0';

            else if (line[*i - 2] == '"')
                args[l][k - *j] = '\0';
            
            else
                args[l][k - *j - 2] = '\0';
        }
        else {
            args[l][k - *j] = '\0';
        }

        l++;
    }

    return l;
}

void free_parser() {

    for (int i = 0; i < count; ++i)
        free(files[i]);

    free(files);
}
