#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lexer/token.c"
#include "../C_array/token_array.c"
#include "../C_map/map.c"
#include "../lexer/lex.c"
#include "../lexer/read_file.c"

void run_test_case(char *test_case_path, TokenArray *expected) {
  TokenArray *arr = initialize_token_array(1);

  const char *src = read_file(test_case_path);

  assert(lex(src, arr));

  assert(expected->size == arr->size);

  for (unsigned int i = 0; i < arr->size; ++i) {
    assert(arr->array[i].kind == expected->array[i].kind);
    assert(!strcmp(arr->array[i].literal, expected->array[i].literal));
  }
}

int main() {
  TokenArray *exp1 = initialize_token_array(1);
  TokenArray *exp2 = initialize_token_array(1);
  TokenArray *exp3 = initialize_token_array(1);

  Token int_keyword = {TOK_INTKEY, "int"};
  Token func_name = {TOK_ID, "main"};
  Token l_paren = {TOK_LPAREN, "("};
  Token r_paren = {TOK_RPAREN, ")"};
  Token l_curly = {TOK_LCURLY, "{"};
  Token ret_keyword = {TOK_RETKEY, "return"};
  Token semicol = {TOK_SEMICOL, ";"};
  Token r_curly = {TOK_RCURLY, "}"};

  push_back_token(exp1, int_keyword);
  push_back_token(exp2, int_keyword);
  push_back_token(exp3, int_keyword);

  push_back_token(exp1, func_name);
  push_back_token(exp2, func_name);
  push_back_token(exp3, func_name);

  push_back_token(exp1, l_paren);
  push_back_token(exp2, l_paren);
  push_back_token(exp3, l_paren);

  push_back_token(exp1, r_paren);
  push_back_token(exp2, r_paren);
  push_back_token(exp3, r_paren);

  push_back_token(exp1, l_curly);
  push_back_token(exp2, l_curly);
  push_back_token(exp3, l_curly);

  push_back_token(exp1, ret_keyword);
  push_back_token(exp2, ret_keyword);
  push_back_token(exp3, ret_keyword);

  Token exp1_int_lit = {TOK_INTLIT, "3"};
  Token exp1_bin_op = {TOK_ADD, "+"};
  Token exp1_int_lit_a = {TOK_INTLIT, "4"};

  Token exp2_int_lit = {TOK_INTLIT, "2"};
  Token exp2_bin_op = {TOK_MULTIPLY, "*"};
  Token exp2_int_lit_a = {TOK_INTLIT, "4"};

  Token exp3_int_lit = {TOK_INTLIT, "6"};
  Token exp3_bin_op = {TOK_DIVIDE, "/"};
  Token exp3_int_lit_a = {TOK_INTLIT, "3"};

  push_back_token(exp1, exp1_int_lit);
  push_back_token(exp1, exp1_bin_op);
  push_back_token(exp1, exp1_int_lit_a);

  push_back_token(exp2, exp2_int_lit);
  push_back_token(exp2, exp2_bin_op);
  push_back_token(exp2, exp2_int_lit_a);
  
  push_back_token(exp3, exp3_int_lit);
  push_back_token(exp3, exp3_bin_op);
  push_back_token(exp3, exp3_int_lit_a);

  push_back_token(exp1, semicol);
  push_back_token(exp2, semicol);
  push_back_token(exp3, semicol);

  push_back_token(exp1, r_curly);
  push_back_token(exp2, r_curly);
  push_back_token(exp3, r_curly);

  run_test_case("test_cases/test_case7.c", exp1);
  run_test_case("test_cases/test_case8.c", exp2);
  run_test_case("test_cases/test_case9.c", exp3);

  printf("All test passed succesfully");
  return 0;
}