#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "../lexer/token.c"
#include "../C_array/char_array.c"
#include "../C_array/token_array.c"
#include "../lexer/lex.c"
#include "../lexer/read_file.c"

void run_test_case(char *test_case_path, TokenArray *expected) {
  TokenArray *arr = initialize_token_array(1);

  const char *src = read_file(test_case_path);

  assert(lex(src, arr));

  
  assert(expected->size == arr->size);

  for (unsigned int i = 0; i < arr->size; ++i) {
    assert(arr->array[i].kind == expected->array[i].kind);
    if (arr->array[i].kind == TOK_INTLIT || arr->array[i].kind == TOK_ID) {
      assert(!strcmp(arr->array[i].literal, expected->array[i].literal));
    }
  }
}

int main() {
  Token int_keyword = {TOK_INTKEY, "int"};
  Token func_name = {TOK_ID, "main"};
  Token l_paren = {TOK_LPAREN, "("};
  Token r_paren = {TOK_RPAREN, ")"};
  Token l_curly = {TOK_LCURLY, "{"};
  Token ret_keyword = {TOK_RETKEY, "return"};
  Token if_key = {TOK_IFKEY, "if"};
  Token else_key = {TOK_ELSEKEY, "else"};
  Token semicol = {TOK_SEMICOL, ";"};
  Token colon = {TOK_COLON, ":"};
  Token qmark = {TOK_QMARK, "?"};
  Token r_curly = {TOK_RCURLY, "}"};
  Token assign = {TOK_ASSIGN, "="};
  Token a = {TOK_ID, "a"};
  Token b = {TOK_ID, "b"};
  Token zero = {TOK_INTLIT, "0"};
  Token one = {TOK_INTLIT, "1"};
  Token two = {TOK_INTLIT, "2"};
  Token three = {TOK_INTLIT, "3"};
  Token four = {TOK_INTLIT, "4"};
  Token plus = {TOK_ADD, "+"};
  Token minus = {TOK_NEGATION, "-"};

  TokenArray *exp1 = initialize_token_array(1);
  
  push_back_token(exp1, int_keyword);
  push_back_token(exp1, func_name);
  push_back_token(exp1, l_paren);
  push_back_token(exp1, r_paren);
  push_back_token(exp1, l_curly);
  push_back_token(exp1, int_keyword);
  push_back_token(exp1, a);
  push_back_token(exp1, assign);
  push_back_token(exp1, zero);
  push_back_token(exp1, semicol);
  push_back_token(exp1, int_keyword);
  push_back_token(exp1, b);
  push_back_token(exp1, assign);
  push_back_token(exp1, one);
  push_back_token(exp1, semicol);
  push_back_token(exp1, if_key);
  push_back_token(exp1, l_paren);
  push_back_token(exp1, a);
  push_back_token(exp1, plus);
  push_back_token(exp1, b);
  push_back_token(exp1, r_paren);
  push_back_token(exp1, l_curly);
  push_back_token(exp1, ret_keyword);
  push_back_token(exp1, three);
  push_back_token(exp1, semicol);
  push_back_token(exp1, r_curly);
  push_back_token(exp1, else_key);
  push_back_token(exp1, l_curly);
  push_back_token(exp1, ret_keyword);
  push_back_token(exp1, two);
  push_back_token(exp1, semicol);
  push_back_token(exp1, r_curly);
  push_back_token(exp1, r_curly);
  
  run_test_case("test_cases/test_case16.c", exp1);

  TokenArray *exp2 = initialize_token_array(1);
  
  push_back_token(exp2, int_keyword);
  push_back_token(exp2, func_name);
  push_back_token(exp2, l_paren);
  push_back_token(exp2, r_paren);
  push_back_token(exp2, l_curly);
  push_back_token(exp2, int_keyword);
  push_back_token(exp2, a);
  push_back_token(exp2, assign);
  push_back_token(exp2, two);
  push_back_token(exp2, semicol);
  push_back_token(exp2, int_keyword);
  push_back_token(exp2, b);
  push_back_token(exp2, assign);
  push_back_token(exp2, three);
  push_back_token(exp2, semicol);
  push_back_token(exp2, if_key);
  push_back_token(exp2, l_paren);
  push_back_token(exp2, a);
  push_back_token(exp2, plus);
  push_back_token(exp2, b);
  push_back_token(exp2, r_paren);
  push_back_token(exp2, l_curly);
  push_back_token(exp2, ret_keyword);
  push_back_token(exp2, one);
  push_back_token(exp2, semicol);
  push_back_token(exp2, r_curly);
  push_back_token(exp2, else_key);
  push_back_token(exp2, if_key);
  push_back_token(exp2, l_paren);
  push_back_token(exp2, b);
  push_back_token(exp2, minus);
  push_back_token(exp2, a);
  push_back_token(exp2, r_paren);
  push_back_token(exp2, l_curly);
  push_back_token(exp2, ret_keyword);
  push_back_token(exp2, four);
  push_back_token(exp2, semicol);
  push_back_token(exp2, r_curly);
  push_back_token(exp2, else_key);
  push_back_token(exp2, l_curly);
  push_back_token(exp2, ret_keyword);
  push_back_token(exp2, zero);
  push_back_token(exp2, semicol);
  push_back_token(exp2, r_curly);
  push_back_token(exp2, r_curly);

  run_test_case("test_cases/test_case17.c", exp2);

  TokenArray *exp3 = initialize_token_array(1);
  
  push_back_token(exp3, int_keyword);
  push_back_token(exp3, func_name);
  push_back_token(exp3, l_paren);
  push_back_token(exp3, r_paren);
  push_back_token(exp3, l_curly);
  push_back_token(exp3, int_keyword);
  push_back_token(exp3, a);
  push_back_token(exp3, assign);
  push_back_token(exp3, zero);
  push_back_token(exp3, semicol);
  push_back_token(exp3, a);
  push_back_token(exp3, assign);
  push_back_token(exp3, one);
  push_back_token(exp3, qmark);
  push_back_token(exp3, two);
  push_back_token(exp3, colon);
  push_back_token(exp3, three);
  push_back_token(exp3, semicol);
  push_back_token(exp3, ret_keyword);
  push_back_token(exp3, a);
  push_back_token(exp3, semicol);
  push_back_token(exp3, r_curly);
  
  run_test_case("test_cases/test_case18.c", exp3);

  printf("All test passed succesfully");
  return 0;
}