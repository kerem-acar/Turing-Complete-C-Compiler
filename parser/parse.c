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
  if (compare_kind(p, TOK_LOGNEG) == 1) {
    return 1;
  }
  if (compare_kind(p, TOK_NEGATION) == 1) {
    return 1;
  }
  if (compare_kind(p, TOK_BITCOMP) == 1) {
    return 1;
  }
  return 0;
}

AST_Expression *parse_expression(Parser *p) {
  p->i++;

  AST_Expression *exp = malloc(sizeof(AST_Expression));

  if (compare_kind(p, TOK_INTLIT) == 1) {
    exp->kind = 0;
    exp->Constant = p->arr->array[p->i].literal;
    return exp;
  } else {
    if (is_unop(p) == 1) {
      exp->UnOp.op = p->arr->array[p->i];
      exp->kind = 1;
      exp->UnOp.exp = parse_expression(p);
      return exp;
    }
  } 
}

int parse_statement(Parser *p, AST_Function *func) {
  if (compare_kind(p, TOK_RETKEY) == 0) {
    return 0;
  }

  AST_Statement *stat = malloc(sizeof(AST_Statement));

  func->body = stat;

  stat->exp = parse_expression(p);

  p->i++;

  if (compare_kind(p, TOK_SEMICOL) == 0) {
    return 0;
  }

  p->i++;

  return 1;
}

int parse_function(Parser *p, AST_Program *prog) {
  if (compare_kind(p, TOK_INTKEY) == 0) {
    return 0;
  }

  p->i++;

  if (compare_kind(p, TOK_ID) == 0 ||
      strcmp(p->arr->array[p->i].literal, "main") != 0) {
    return 0;
  }

  AST_Function *func = malloc(sizeof(AST_Function));

  prog->func = func;

  func->name = "main";

  p->i++;

  if (compare_kind(p, TOK_LPAREN) == 0) {
    return 0;
  }

  p->i++;

  if (compare_kind(p, TOK_RPAREN) == 0) {
    return 0;
  }

  p->i++;

  if (compare_kind(p, TOK_LCURLY) == 0) {
    return 0;
  }

  p->i++;

  if (parse_statement(p, func) != 1) {  
    return 0;
  }

  if (compare_kind(p, TOK_RCURLY) == 0) {
    return 0;
  }

  p->i++;

  return 1;
}