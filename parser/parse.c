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

int compare_kind(Parser *p, TOK kind) {
  if (p->arr->array[p->i].kind != kind) {
    return 0;
  }
  return 1;
}

int is_unop(Parser *p) {
  switch(p->arr->array[p->i].kind) {
  case TOK_LOGNEG:
  case TOK_NEGATION:
  case TOK_BITCOMP: {
    return 1;
  } break;
  }
  
  return 0;
}

AST_Expression *parse_expression(Parser *p) {
  p->i++;

  AST_Expression *exp = malloc(sizeof(AST_Expression));

  if (compare_kind(p, TOK_INTLIT)) {
    exp->kind = 0;
    exp->Constant = p->arr->array[p->i].literal;
  } else if (is_unop(p)) {
    exp->UnOp.op = p->arr->array[p->i];
    exp->kind = 1;
    exp->UnOp.exp = parse_expression(p);
  } else {
    assert(0);
  }

  return exp;
}

int parse_statement(Parser *p, AST_Function *func) {
  if (!compare_kind(p, TOK_RETKEY)) {
    return 0;
  }

  AST_Statement *stat = malloc(sizeof(AST_Statement));

  func->body = stat;

  stat->exp = parse_expression(p);

  p->i++;

  if (!compare_kind(p, TOK_SEMICOL)) {
    return 0;
  }

  p->i++;

  return 1;
}

int parse_function(Parser *p, AST_Program *prog) {
  if (!compare_kind(p, TOK_INTKEY)) {
    return 0;
  }

  p->i++;

  if (!compare_kind(p, TOK_ID) ||
      strcmp(p->arr->array[p->i].literal, "main") != 0) {
    return 0;
  }

  AST_Function *func = malloc(sizeof(AST_Function));

  prog->func = func;

  func->name = "main";

  p->i++;

  if (!compare_kind(p, TOK_LPAREN)) {
    return 0;
  }

  p->i++;

  if (!compare_kind(p, TOK_RPAREN)) {
    return 0;
  }

  p->i++;

  if (!compare_kind(p, TOK_LCURLY)) {
    return 0;
  }

  p->i++;

  if (!parse_statement(p, func)) {
    return 0;
  }

  if (!compare_kind(p, TOK_RCURLY)) {
    return 0;
  }

  p->i++;

  return 1;
}