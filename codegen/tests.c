#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "../C_map/map.c"
#include "../lexer/token.c"
#include "../C_array/token_array.c"
#include "../C_array/char_array.c"
#include "../lexer/lex.c"
#include "../lexer/read_file.c"
#include "../parser/ast.c"
#include "../parser/parse.c"
#include "../parser/print.c"
#include "../codegen/write_to_file.c"
#include "../codegen/gen.c"

void run_test_case(char *test_case_path, char *test_result_path, int id) {
  TokenArray *arr = initialize_token_array(1);

  const char *src = read_file(test_case_path);

  lex(src, arr);

  Parser *p = initialize_parser(arr);

  AST_Program *prog = malloc(sizeof(AST_Program));

  parse_function(p, prog);

  CharArray *char_arr = initialize_char_array(1);

  assert(generate_function(prog, test_result_path, char_arr, id) == 1);
}

int main() {
  int id = 1;

  run_test_case("test_cases/test_case13.c", "codegen/test1_result.s", id);
  id += 1;

  run_test_case("test_cases/test_case14.c", "codegen/test2_result.s", id);
  id += 1;
  
  run_test_case("test_cases/test_case15.c", "codegen/test3_result.s", id);
  id += 1;
  
  printf("All tests passed");
  return 0;
}