#include "lex.c"

int main() {
  char *file_path1 = "test_cases/test_case4.c";
  char *file_path2 = "test_cases/test_case5.c";
  char *file_path3 = "test_cases/test_case6.c";

  TokenArray *arr1 = initialize_token_array(1);
  TokenArray *arr2 = initialize_token_array(1);
  TokenArray *arr3 = initialize_token_array(1);

  const char *s1 = read_file(file_path1);
  const char *s2 = read_file(file_path2);
  const char *s3 = read_file(file_path3);

  assert(lex(s1, arr1) == 1);
  assert(lex(s2, arr2) == 1);
  assert(lex(s3, arr3) == 1);

  printf("tests passed successfully\n");

  for (int i = 0; i < arr1->size; ++i) {
    printf("%s\n", arr1->array[i].literal);
  }

  for (int i = 0; i < arr2->size; ++i) {
    printf("%s\n", arr2->array[i].literal);
  }

  for (int i = 0; i < arr3->size; ++i) {
    printf("%s\n", arr3->array[i].literal);
  }

  return 0;
}