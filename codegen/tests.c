#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "../lexer/token.c"
#include "../C_array/token_array.c"
#include "../C_array/char_array.c"
#include "../C_map/map.c"
#include "../lexer/lex.c"
#include "../lexer/read_file.c"
#include "../parser/ast.c"
#include "../parser/parse.c"
#include "../parser/print.c"
#include "../codegen/write_to_file.c"
#include "../codegen/gen.c"

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

  char *test_path1 = "codegen/test1_result.s";
  char *test_path2 = "codegen/test2_result.s";
  char *test_path3 = "codegen/test3_result.s";

  CharArray *char_arr1 = initialize_char_array(1);
  CharArray *char_arr2 = initialize_char_array(1);
  CharArray *char_arr3 = initialize_char_array(1);

  int id = 1;

  assert(generate_function(prog_1, test_path1, char_arr1, id) == 1);
  id += 1;
  assert(generate_function(prog_2, test_path2, char_arr2, id) == 1);
  id += 1;
  assert(generate_function(prog_3, test_path3, char_arr3, id) == 1);
  id += 1;
  
  printf("All tests passed");
  return 0;
}