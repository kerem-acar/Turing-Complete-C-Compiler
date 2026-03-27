#include "stdio.h"
#include "string.h"

int write_function_name_to_file(char *file_path, char *func_name) {
    FILE *fptr = fopen(file_path, "w");

    if (fptr == NULL) {
        return 0;
    }

    fprintf(fptr, "%s:\n", func_name);
    fclose(fptr);
    return 1;
}

int write_return_statement(char *file_path, char *constant) {
    FILE *fptr = fopen(file_path, "a");

    if (fptr == NULL) {
        return 0;
    }

    fprintf(fptr, "        mov      eax, %s\n", constant);
    fprintf(fptr, "        ret");

    fclose(fptr);
    return 1;
}