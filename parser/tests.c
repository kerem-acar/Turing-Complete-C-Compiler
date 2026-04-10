#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lexer/token.c"
#include "../C_array/token_array.c"
#include "../C_map/map.c"
#include "../lexer/lex.c"
#include "../lexer/read_file.c"
#include "../parser/ast.c"
#include "../parser/parse.c"
#include "../parser/print.c"

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

  assert(parse_function(p1, prog_1) == 1);
  assert(parse_function(p2, prog_2) == 1);
  assert(parse_function(p3, prog_3) == 1);

  print_program_node(prog_1);
  print_program_node(prog_2);
  print_program_node(prog_3);

  return 0;
}