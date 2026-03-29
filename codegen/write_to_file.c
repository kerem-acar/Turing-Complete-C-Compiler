#include "../C_array/char_array.c"
#include "stdio.h"
#include "string.h"

int write_string_to_file(char *file_path, CharArray *arr) {
  FILE *fptr = fopen(file_path, "w");

  if (fptr == NULL) {
    return 0;
  }

  int i = 0;

  while (arr->array[i]) {
    fprintf(fptr, "%c", arr->array[i]);
    i++;
  }

  fclose(fptr);
  return 1;
}