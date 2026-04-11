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

void run_test_case(char *test_case_path) {
  TokenArray *arr = initialize_token_array(1);

  const char *src = read_file(test_case_path);

  lex(src, arr);

  Parser *p = initialize_parser(arr);

  AST_Program *prog = malloc(sizeof(AST_Program));

  assert(parse_function(p, prog) == 1);

  print_program_node(prog);


}

int main() {
  

  run_test_case("test_cases/test_case4.c");
  run_test_case("test_cases/test_case5.c");
  run_test_case("test_cases/test_case6.c");

  printf("All test cases passed");
  return 0;
}