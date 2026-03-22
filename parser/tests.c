#include "../lexer/lex.c"
#include "parse.c"

int main() {

  char *file_path1 = "../test_cases/test_case1.c";
  char *file_path2 = "../test_cases/test_case2.c";
  char *file_path3 = "../test_cases/test_case3.c";

  TokenArray *arr1 = initialize_token_array(1);
  TokenArray *arr2 = initialize_token_array(1);
  TokenArray *arr3 = initialize_token_array(1);

  const char *s1 = read_file(file_path1);
  const char *s2 = read_file(file_path2);
  const char *s3 = read_file(file_path3);

  lex(s1, arr1);
  lex(s2, arr2);
  lex(s3, arr3);

  Parser *p1 = initialize_parser(arr1);
  Parser *p2 = initialize_parser(arr1);
  Parser *p3 = initialize_parser(arr1);

  int parse_one_result = parse_function(p1);
  int parse_two_result = parse_function(p2);
  int parse_three_result = parse_function(p3);

  printf("%d\n", parse_one_result);
  printf("%d\n", parse_two_result);
  printf("%d\n", parse_three_result);
  
  return 0;
}