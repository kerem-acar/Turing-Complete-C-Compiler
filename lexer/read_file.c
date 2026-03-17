#include <stdio.h>
#include <stdlib.h>

const char *read_file(const char *filename) {
  FILE *file = fopen(filename, "rb");
  if (!file) {
    perror("Failed to open file");
    return NULL;
  }


  fseek(file, 0, SEEK_END);

  long size = ftell(file);

  rewind(file);

  char *buffer = (char *)malloc(size + 1);
  if (!buffer) {
    perror("Failed to allocate memory");
    fclose(file);
    return NULL;
  }

  size_t read_size = fread(buffer, 1, size, file);
  buffer[read_size] = '\0';

  fclose(file);
  return buffer;
}