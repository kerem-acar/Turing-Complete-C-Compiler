#pragma once

typedef enum TOK {
  TOK_LBRACKET,
  TOK_RBRACKET,
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_SEMICOL,
  TOK_RETKEY,
  TOK_INTKEY,
  TOK_ID,
  TOK_INTLIT,
  TOK_UNK
} TOK;

typedef struct Token {
  TOK kind;
  char *literal;
} Token;
