#include "../C_array/array.c"
#include "ast.c"

int parse_expression(TokenArray *arr, int *i) {
  if (arr->array[*i].kind != TOK_INTLIT) {
    return 0;
  }

  (*i)++;
  return 1;
}

int parse_statement(TokenArray *arr, int *i) {
  if (arr->array[*i].kind != TOK_RETKEY) {
    return 0;
  }

  (*i)++;

  if (parse_expression(arr, i) != 1) {
    return 0;
  }

  if (arr->array[*i].kind != TOK_SEMICOL) {
    return 0;
  }

  (*i)++;

  return 1;
}

int parse_function(TokenArray *arr) {
  int i = 0;

  if (arr->array[i].kind != TOK_INTKEY) {
    return 0;
  }

  i++;

  if (arr->array[i].kind != TOK_ID && arr->array[i].literal != "main") {
    return 0;
  }

  i++;

  if (arr->array[i].kind != TOK_LPAREN) {
    return 0;
  }

  i++;

  if (arr->array[i].kind != TOK_RPAREN) {
    return 0;
  }

  i++;

  if (arr->array[i].kind != TOK_LBRACKET) {
    return 0;
  }

  i++;

  if (parse_statement(arr, &i) != 1) {
    return 0;
  }

  if (arr->array[i].kind != TOK_RBRACKET) {
    return 0;
  }

  i++;

  return 1;
}