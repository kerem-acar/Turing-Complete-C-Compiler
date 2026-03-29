#include "../C_stoi/stoi.c"
#include "../lexer/lex.c"
#include "gen.c"

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
  Parser *p2 = initialize_parser(arr2);
  Parser *p3 = initialize_parser(arr3);

  AST_Program *prog_1 = malloc(sizeof(AST_Program));
  AST_Program *prog_2 = malloc(sizeof(AST_Program));
  AST_Program *prog_3 = malloc(sizeof(AST_Program));

  parse_function(p1, prog_1);
  parse_function(p2, prog_2);
  parse_function(p3, prog_3);

  char *test_path1 = "test1_result.s";
  char *test_path2 = "test2_result.s";
  char *test_path3 = "test3_result.s";

  CharArray *char_arr1 = initialize_char_array(1);
  CharArray *char_arr2 = initialize_char_array(1);
  CharArray *char_arr3 = initialize_char_array(1);

  assert(generate(prog_1, test_path1, char_arr1) == 1);
  assert(generate(prog_2, test_path2, char_arr2) == 1);
  assert(generate(prog_3, test_path3, char_arr3) == 1);

  return 0;
}