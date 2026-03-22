#include "../C_array/array.c"
#include "ast.c"
#include <string.h>

typedef struct Parser {
  TokenArray *arr;
  int i;
} Parser;


Parser *initialize_parser(TokenArray *arr) {
  Parser *p = malloc(sizeof(Parser));
  
  p->arr = arr;
  p->i = 0;

  return p;
}


int parse_expression(Parser *p) {
  if (p->arr->array[p->i].kind != TOK_INTLIT) {
    return 0;
  }

  p->i++;
  return 1;
}

int parse_statement(Parser *p) {
  if (p->arr->array[p->i].kind != TOK_RETKEY) {
    return 0;
  }

  p->i++;

  if (parse_expression(p) != 1) {
    return 0;
  }

  if (p->arr->array[p->i].kind != TOK_SEMICOL) {
    return 0;
  }

  p->i++;

  return 1;
}

int parse_function(Parser *p) {

  if (p->arr->array[p->i].kind != TOK_INTKEY) {
    return 0;
  }

  p->i++;

  if (p->arr->array[p->i].kind != TOK_ID && strcmp(p->arr->array[p->i].literal, "main") != 0) {
    return 0;
  }

  p->i++;

  if (p->arr->array[p->i].kind != TOK_LPAREN) {
    return 0;
  }

  p->i++;

  if (p->arr->array[p->i].kind != TOK_RPAREN) {
    return 0;
  }

  p->i++;

  if (p->arr->array[p->i].kind != TOK_LCURLY) {
    return 0;
  }

  p->i++;

  if (parse_statement(p) != 1) {
    return 0;
  }

  if (p->arr->array[p->i].kind != TOK_RCURLY) {
    return 0;
  }

  p->i++;

  return 1;
}