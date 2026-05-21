#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "../C_map/hash.c"
#include "../C_map/map.c"
#include "../C_set/set.c"
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

void compile(char *src_file_path, char *result_path, int id) {
  TokenArray *arr = initialize_token_array(1);

  const char *src = read_file(src_file_path);

  lex(src, arr);

  Parser *p = initialize_parser(arr);

  AST_Program *prog = malloc(sizeof(AST_Program));

  parse_function(p, prog);

  CharArray *char_arr = initialize_char_array(1);

  assert(generate_function(prog, result_path, char_arr, id) == 1);
}

int main() {
  compile("src/input.c", "codegen/result.s", 1);

  return 0;
}