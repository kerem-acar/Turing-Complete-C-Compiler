#include "../lexer/lex.c"
#include "parse.c"

int main() {

  char *file_path1 = "../test_cases/test_case1.c";
  char *file_path2 = "../test_cases/test_case2.c";
  char *file_path3 = "../test_cases/test_case3.c";

  TokenArray *arr1 = initialize_int_array(1);
  TokenArray *arr2 = initialize_int_array(1);
  TokenArray *arr3 = initialize_int_array(1);

  lex(file_path1, arr1);
  lex(file_path2, arr2);
  lex(file_path3, arr3);

  int parse_one_result = parse_function(arr1);
  int parse_two_result = parse_function(arr2);
  int parse_three_result = parse_function(arr3);

  printf("%d\n", parse_one_result);
  printf("%d\n", parse_two_result);
  printf("%d\n", parse_three_result);

  return 0;
}