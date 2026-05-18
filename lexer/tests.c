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
  Token for_key = {TOK_FORKEY, "for"};
  Token while_key = {TOK_WHILEKEY, "while"};
  Token do_key = {TOK_DOKEY, "do"};
  Token break_key = {TOK_BREAKKEY, "break"};
  Token cont_key = {TOK_CONTKEY, "continue"};
  Token logneg = {TOK_LOGNEG, "!"};
  Token logle = {TOK_LOGLE, "<"};
  Token logge = {TOK_LOGGE, ">"};
  Token mult = {TOK_MULTIPLY, "*"};
  Token sum_id = {TOK_ID, "sum"};
  Token i_id = {TOK_ID, "i"};
  Token five = {TOK_INTLIT, "5"};
  Token ten = {TOK_INTLIT, "10"};
  Token eleven = {TOK_INTLIT, "11"};

  TokenArray *exp1 = initialize_token_array(1);
  push_back_token(exp1, int_keyword);
  push_back_token(exp1, func_name);
  push_back_token(exp1, l_paren);
  push_back_token(exp1, r_paren);
  push_back_token(exp1, l_curly);
  push_back_token(exp1, int_keyword);
  push_back_token(exp1, sum_id);
  push_back_token(exp1, assign);
  push_back_token(exp1, zero);
  push_back_token(exp1, semicol);
  push_back_token(exp1, for_key);
  push_back_token(exp1, l_paren);
  push_back_token(exp1, int_keyword);
  push_back_token(exp1, i_id);
  push_back_token(exp1, assign);
  push_back_token(exp1, zero);
  push_back_token(exp1, semicol);
  push_back_token(exp1, i_id);
  push_back_token(exp1, logle);
  push_back_token(exp1, ten);
  push_back_token(exp1, semicol);
  push_back_token(exp1, i_id);
  push_back_token(exp1, assign);
  push_back_token(exp1, i_id);
  push_back_token(exp1, plus);
  push_back_token(exp1, one);
  push_back_token(exp1, r_paren);
  push_back_token(exp1, l_curly);
  push_back_token(exp1, if_key);
  push_back_token(exp1, l_paren);
  push_back_token(exp1, logneg);
  push_back_token(exp1, l_paren);
  push_back_token(exp1, sum_id);
  push_back_token(exp1, minus);
  push_back_token(exp1, four);
  push_back_token(exp1, r_paren);
  push_back_token(exp1, r_paren);
  push_back_token(exp1, l_curly);
  push_back_token(exp1, cont_key);
  push_back_token(exp1, semicol);
  push_back_token(exp1, r_curly);
  push_back_token(exp1, sum_id);
  push_back_token(exp1, assign);
  push_back_token(exp1, sum_id);
  push_back_token(exp1, plus);
  push_back_token(exp1, one);
  push_back_token(exp1, semicol);
  push_back_token(exp1, if_key);
  push_back_token(exp1, l_paren);
  push_back_token(exp1, sum_id);
  push_back_token(exp1, logge);
  push_back_token(exp1, ten);
  push_back_token(exp1, r_paren);
  push_back_token(exp1, l_curly);
  push_back_token(exp1, break_key);
  push_back_token(exp1, semicol);
  push_back_token(exp1, r_curly);
  push_back_token(exp1, r_curly);
  push_back_token(exp1, ret_keyword);
  push_back_token(exp1, sum_id);
  push_back_token(exp1, semicol);
  push_back_token(exp1, r_curly);

  run_test_case("test_cases/test_case22.c", exp1);

  TokenArray *exp2 = initialize_token_array(1);
  push_back_token(exp2, int_keyword);
  push_back_token(exp2, func_name);
  push_back_token(exp2, l_paren);
  push_back_token(exp2, r_paren);
  push_back_token(exp2, l_curly);
  push_back_token(exp2, int_keyword);
  push_back_token(exp2, a);
  push_back_token(exp2, assign);
  push_back_token(exp2, one);
  push_back_token(exp2, semicol);
  push_back_token(exp2, do_key);
  push_back_token(exp2, l_curly);
  push_back_token(exp2, a);
  push_back_token(exp2, assign);
  push_back_token(exp2, a);
  push_back_token(exp2, mult);
  push_back_token(exp2, two);
  push_back_token(exp2, semicol);
  push_back_token(exp2, if_key);
  push_back_token(exp2, l_paren);
  push_back_token(exp2, logneg);
  push_back_token(exp2, l_paren);
  push_back_token(exp2, a);
  push_back_token(exp2, minus);
  push_back_token(exp2, two);
  push_back_token(exp2, r_paren);
  push_back_token(exp2, r_paren);
  push_back_token(exp2, l_curly);
  push_back_token(exp2, break_key);
  push_back_token(exp2, semicol);
  push_back_token(exp2, r_curly);
  push_back_token(exp2, r_curly);
  push_back_token(exp2, while_key);
  push_back_token(exp2, l_paren);
  push_back_token(exp2, a);
  push_back_token(exp2, logle);
  push_back_token(exp2, eleven);
  push_back_token(exp2, r_paren);
  push_back_token(exp2, semicol);
  push_back_token(exp2, ret_keyword);
  push_back_token(exp2, a);
  push_back_token(exp2, semicol);
  push_back_token(exp2, r_curly);

  run_test_case("test_cases/test_case23.c", exp2);

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
  push_back_token(exp3, int_keyword);
  push_back_token(exp3, b);
  push_back_token(exp3, assign);
  push_back_token(exp3, one);
  push_back_token(exp3, semicol);
  push_back_token(exp3, while_key);
  push_back_token(exp3, l_paren);
  push_back_token(exp3, a);
  push_back_token(exp3, logle);
  push_back_token(exp3, five);
  push_back_token(exp3, r_paren);
  push_back_token(exp3, l_curly);
  push_back_token(exp3, a);
  push_back_token(exp3, assign);
  push_back_token(exp3, a);
  push_back_token(exp3, plus);
  push_back_token(exp3, two);
  push_back_token(exp3, semicol);
  push_back_token(exp3, b);
  push_back_token(exp3, assign);
  push_back_token(exp3, b);
  push_back_token(exp3, mult);
  push_back_token(exp3, a);
  push_back_token(exp3, semicol);
  push_back_token(exp3, if_key);
  push_back_token(exp3, l_paren);
  push_back_token(exp3, logneg);
  push_back_token(exp3, l_paren);
  push_back_token(exp3, a);
  push_back_token(exp3, minus);
  push_back_token(exp3, b);
  push_back_token(exp3, r_paren);
  push_back_token(exp3, r_paren);
  push_back_token(exp3, l_curly);
  push_back_token(exp3, break_key);
  push_back_token(exp3, semicol);
  push_back_token(exp3, r_curly);
  push_back_token(exp3, r_curly);
  push_back_token(exp3, ret_keyword);
  push_back_token(exp3, a);
  push_back_token(exp3, semicol);
  push_back_token(exp3, r_curly);

  run_test_case("test_cases/test_case24.c", exp3);

  printf("All test passed succesfully\n");
  return 0;
}