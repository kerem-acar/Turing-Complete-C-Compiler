typedef enum TOK {
  TOK_LCURLY,
  TOK_RCURLY,
  TOK_LPAREN,
  TOK_RPAREN,
  TOK_SEMICOL,
  TOK_RETKEY,
  TOK_INTKEY,
  TOK_ID,
  TOK_INTLIT,
  TOK_UNK,
  TOK_NEGATION,
  TOK_BITCOMP,
  TOK_LOGNEG,
  TOK_ADD,
  TOK_MULTIPLY,
  TOK_DIVIDE
} TOK;

typedef struct Token {
  TOK kind;
  char *literal;
} Token;
