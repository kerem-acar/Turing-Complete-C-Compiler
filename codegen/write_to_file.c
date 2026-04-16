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

int write_tokens_to_file(char *file_path, TokenArray *arr) {  
  FILE *fptr = fopen(file_path, "w");

  if (fptr == NULL) {
    return 0;
  }

  for (unsigned int i = 0; i < arr->size; ++i) {
    fprintf(fptr, "%s ", arr->array[i].literal);
  }

  fclose(fptr);
  return 1;
}