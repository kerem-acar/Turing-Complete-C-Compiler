#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../parser/compare_strings.c"
#include "../lexer/token.c"
#include "../parser/ast.c"
#include "../C_array/char_array.c"
#include "../C_array/token_array.c"
#include "../lexer/lex.c"
#include "../lexer/read_file.c"
#include "../parser/parse.c"
#include "../parser/print.c"

void run_test_case(char *test_case_path, char *result_file_path, char *expected_file_path) {
  TokenArray *arr = initialize_token_array(1);

  const char *src = read_file(test_case_path);

  lex(src, arr);

  Parser *p = initialize_parser(arr);

  AST_Program *prog = malloc(sizeof(AST_Program));

  assert(parse_function(p, prog));

  print_program_node(prog, result_file_path);

  char *s1 = read_file(result_file_path);
  char *s2 = read_file(expected_file_path);

  assert(compare(s1, s2));
}

int main() {
  run_test_case("test_cases/test_case13.c", "parser/test1_result.txt", "parser/test1_expected.txt");
  run_test_case("test_cases/test_case14.c", "parser/test2_result.txt", "parser/test2_expected.txt");
  run_test_case("test_cases/test_case15.c", "parser/test3_result.txt", "parser/test3_expected.txt");

  printf("All test cases passed");
  return 0;
}