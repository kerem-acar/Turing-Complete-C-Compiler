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

Token get_token(Parser *p) {
  return p->arr->array[p->i];
}

Token get_next_token(Parser *p) {
  return p->arr->array[p->i + 1];
}

int compare_kind(Parser *p, TOK kind) {
  if (get_token(p).kind != kind) {
    return 0;
  }
  return 1;
}

void advance(Parser *p) {
  p->i++;
}

int match_token(Parser *p, TOK kind) {
  if (!compare_kind(p, kind)) {
    return 0;
  }

  advance(p);

  return 1;
}

int is_unop(Parser *p) {
  switch(get_token(p).kind) {
  case TOK_LOGNEG:
  case TOK_NEGATION:
  case TOK_BITCOMP: {
    return 1;
  } break;
  }
  
  return 0;
}

AST_Expression *create_constant(Parser *p) {
  AST_Expression *exp = malloc(sizeof(AST_Expression));
  
  exp->kind = EXP_CONSTANT;
  exp->Constant = get_token(p).literal;

  return exp;
}

AST_Expression *create_unop(Parser *p) {
  AST_Expression *exp = malloc(sizeof(AST_Expression));

  exp->kind = EXP_UN_OP;
  exp->UnOp.un_op = get_token(p);  
  exp->UnOp.exp = NULL;

  return exp;
}

AST_Expression *create_binop(AST_Expression *left, AST_Expression *right, Token op) {
  AST_Expression *exp = malloc(sizeof(AST_Expression));

  exp->kind = EXP_BIN_OP;
  exp->BinOp.left_exp = left;
  exp->BinOp.right_exp = right;
  exp->BinOp.bin_op = op;

  return exp;
}

AST_Expression *parse_expression(Parser *p);

AST_Expression *parse_factor(Parser *p) {
  AST_Expression *exp;

  if (match_token(p, TOK_LPAREN)) {
    exp = parse_expression(p);

    if (!match_token(p, TOK_RPAREN)) {
      assert(0);
    }
  } else if (is_unop(p)) {
    exp = create_unop(p);
    advance(p);
    exp->UnOp.exp = parse_factor(p);
  } else if (compare_kind(p, TOK_INTLIT)) {
    exp = create_constant(p);
    advance(p);
  } else if (compare_kind(p, TOK_ID)) {
    exp = malloc(sizeof(AST_Expression));

    exp->kind = EXP_REF;
    exp->Reference.name = get_token(p).literal;

    advance(p);
  } else {
    assert(0);
  }

  return exp;
}

AST_Expression *parse_term(Parser *p) {
  AST_Expression *exp1 = parse_factor(p);

  Token curr = get_token(p);

  while (curr.kind == TOK_MULTIPLY || curr.kind == TOK_DIVIDE) {
    advance(p);
    AST_Expression *exp2 = parse_factor(p);

    AST_Expression *new_bin_op = create_binop(exp1, exp2, curr);
    
    exp1 = new_bin_op;
    
    curr = get_token(p);
  }

  return exp1;
}

AST_Expression *parse_additive_expression(Parser *p) {
  AST_Expression *exp1 = parse_term(p);

  Token curr = get_token(p);

  while (curr.kind == TOK_ADD || curr.kind == TOK_NEGATION) {
    advance(p);
    AST_Expression *exp2 = parse_term(p);

    AST_Expression *new_bin_op = create_binop(exp1, exp2, curr);

    exp1 = new_bin_op;

    curr = get_token(p);
  }

  return exp1;
}

AST_Expression *parse_relational_expression(Parser *p) {
  AST_Expression *exp1 = parse_additive_expression(p);

  Token curr = get_token(p);

  while (curr.kind == TOK_LOGLE || curr.kind == TOK_LOGLEQ || curr.kind == TOK_LOGGE || curr.kind == TOK_LOGGEQ) {
    advance(p);
    AST_Expression *exp2 = parse_additive_expression(p);

    AST_Expression *new_bin_op = create_binop(exp1, exp2, curr);

    exp1 = new_bin_op;

    curr = get_token(p);
  }

  return exp1;
}

AST_Expression *parse_equality_expression(Parser *p) {
  AST_Expression *exp1 = parse_relational_expression(p);

  Token curr = get_token(p);

  while (curr.kind == TOK_LOGNEQ || curr.kind == TOK_LOGEQ) {
    advance(p);
    AST_Expression *exp2 = parse_relational_expression(p);

    AST_Expression *new_bin_op = create_binop(exp1, exp2, curr);

    exp1 = new_bin_op;

    curr = get_token(p);
  }

  return exp1;
}

AST_Expression *parse_logical_and_expression(Parser *p) {
  AST_Expression *exp1 = parse_equality_expression(p);

  Token curr = get_token(p);

  while (curr.kind == TOK_LOGAND) {
    advance(p);
    AST_Expression *exp2 = parse_equality_expression(p);

    AST_Expression *new_bin_op = create_binop(exp1, exp2, curr);

    exp1 = new_bin_op;

    curr = get_token(p);
  }

  return exp1;
}

AST_Expression *parse_logical_or_expression(Parser *p) {
  AST_Expression *exp1 = parse_logical_and_expression(p);

  Token curr = get_token(p);

  while (curr.kind == TOK_LOGOR) {
    advance(p);
    AST_Expression *exp2 = parse_logical_and_expression(p);

    AST_Expression *new_bin_op = create_binop(exp1, exp2, curr);

    exp1 = new_bin_op;

    curr = get_token(p);
  }

  return exp1;
}

AST_Expression *parse_expression(Parser *p) {
  AST_Expression *exp;
  
  if (compare_kind(p, TOK_ID) && get_next_token(p).kind == TOK_ASSIGN) {
    exp = malloc(sizeof(AST_Expression));

    exp->kind = EXP_ASSIGN;
    exp->Assign.name = get_token(p).literal;
    advance(p);

    if (!match_token(p, TOK_ASSIGN)) {
      assert(0);
    }

    exp->Assign.exp = parse_expression(p);
  } else {
    exp = parse_logical_or_expression(p);
  }

  return exp;
}

int parse_statement(Parser *p, AST_Function *func) {
  AST_Statement *stat = malloc(sizeof(AST_Statement));

  
  if (match_token(p, TOK_RETKEY)) {
    stat->kind = STAT_RETURN;
    stat->Return.exp = parse_expression(p);
  } else if (match_token(p, TOK_INTKEY)) {
    stat->kind = STAT_DECLARE;

    if (compare_kind(p, TOK_ID)) {
      stat->Declare.name = get_token(p).literal;
      advance(p);
    } else {
      return 0;
    }

    if (match_token(p, TOK_ASSIGN)) {
      stat->Declare.exp = parse_expression(p);
    } else {
      stat->Declare.exp = NULL;
    }
  } else {
    stat->kind = STAT_EXP;
    stat->Expression.exp = parse_expression(p);
  }

  if (!match_token(p, TOK_SEMICOL)) {
    return 0;
  }

  push_back_stat(func->body, (*stat));

  return 1;
}

int parse_function(Parser *p, AST_Program *prog) {
  if (!match_token(p, TOK_INTKEY)) {
    return 0;
  }

  if (strcmp(get_token(p).literal, "main") != 0 || !match_token(p, TOK_ID)) {
    return 0;
  }

  AST_Function *func = malloc(sizeof(AST_Function));

  prog->func = func;

  func->name = "main";
  func->body = initialize_stat_array(1);

  if (!match_token(p, TOK_LPAREN)) {
    return 0;
  }

  if (!match_token(p, TOK_RPAREN)) {
    return 0;
  }

  if (!match_token(p, TOK_LCURLY)) {
    return 0;
  }

  while (p->i < p->arr->size && !compare_kind(p, TOK_RCURLY)) {
    int status = parse_statement(p, func);

    if (!status) {
      return 0;
    }
  }

  if (!match_token(p, TOK_RCURLY)) {
    return 0;
  }

  return 1;
}