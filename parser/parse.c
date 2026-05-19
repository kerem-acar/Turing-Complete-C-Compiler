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

AST_Expression *create_placeholder() {
  AST_Expression *exp = malloc(sizeof(AST_Expression));

  exp->kind = EXP_CONSTANT;

  char *literal = malloc(sizeof(char) * 2);

  literal[0] = '1';
  literal[1] = '\0';

  exp->Constant = literal;

  return exp;
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

AST_Expression *create_reference(Parser *p) {
  AST_Expression *exp = malloc(sizeof(AST_Expression));

  exp->kind = EXP_REF;
  exp->Reference = get_token(p).literal;

  return exp;
}

AST_Expression *create_assignment(Parser *p) {
  AST_Expression *exp = malloc(sizeof(AST_Expression));

  exp->kind = EXP_ASSIGN;
  exp->Assign.name = get_token(p).literal;

  return exp;
}

AST_Expression *create_conditional_expression(AST_Expression *e1, AST_Expression *e2, AST_Expression *e3) {
  AST_Expression *exp = malloc(sizeof(AST_Expression));
  exp->kind = EXP_COND;
  
  exp->CondExp.e1 = e1;
  exp->CondExp.e2 = e2;
  exp->CondExp.e3 = e3;
  
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
    exp = create_reference(p);
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

AST_Expression *parse_conditional_expression(Parser *p) {
  AST_Expression *e1 = parse_logical_or_expression(p);
  AST_Expression *e2 = NULL;
  AST_Expression *e3 = NULL;

  if (match_token(p, TOK_QMARK)) {
    e2 = parse_expression(p);
    
    if (!match_token(p, TOK_COLON)) {
      assert(0);
    }

    e3 = parse_conditional_expression(p);

    return create_conditional_expression(e1, e2, e3);
  }

  return e1;
}

AST_Expression *parse_expression(Parser *p) {
  AST_Expression *exp;
  
  if (compare_kind(p, TOK_ID) && get_next_token(p).kind == TOK_ASSIGN) {
    exp = create_assignment(p);
    advance(p);

    if (!match_token(p, TOK_ASSIGN)) {
      assert(0);
    }

    exp->Assign.exp = parse_expression(p);
  } else {
    exp = parse_conditional_expression(p);
  }

  return exp;
}
AST_Declaration *parse_declaration(Parser *p);
int parse_block_item(Parser *p, BlockArray *arr);

AST_Statement *parse_statement(Parser *p) {
  AST_Statement *stat = malloc(sizeof(AST_Statement));

  if (match_token(p, TOK_RETKEY)) {
    stat->kind = STAT_RETURN;
    stat->Return = parse_expression(p);

    if (!match_token(p, TOK_SEMICOL)) {
      assert(0);
    }
  } else if (match_token(p, TOK_IFKEY)) {
    stat->kind = STAT_IF;

    if (!match_token(p, TOK_LPAREN)) {
      assert(0);
    }

    stat->If.exp = parse_expression(p);

    if (!match_token(p, TOK_RPAREN)) {
      assert(0);
    }

    if (!compare_kind(p, TOK_LCURLY)) {
      assert(0);
    }

    stat->If.stat = parse_statement(p); 

    if (match_token(p, TOK_ELSEKEY)) {
      if (compare_kind(p, TOK_IFKEY)) {
        stat->If.optional_stat = parse_statement(p);
      } else {
        if (!compare_kind(p, TOK_LCURLY)) {
          assert(0);
        }

        stat->If.optional_stat = parse_statement(p);
      }
    } else {
      stat->If.optional_stat = NULL;
    }
  } else if (match_token(p, TOK_LCURLY)) {
    stat->kind = STAT_COMP;
    stat->Compound = initialize_block_array(1);
    
    while (p->i < p->arr->size && !compare_kind(p, TOK_RCURLY)) {
      int status = parse_block_item(p, stat->Compound);

      if (!status) {
        return 0;
      }
    }

    if (!match_token(p, TOK_RCURLY)) {
      assert(0);
    }
  } else if (match_token(p, TOK_FORKEY)) {
    if (!match_token(p, TOK_LPAREN)) {
      assert(0);
    }

    if (compare_kind(p, TOK_INTKEY)) {
      stat->kind = STAT_FORDEC;

      stat->ForDecl.dec = parse_declaration(p);

      if (match_token(p, TOK_SEMICOL)) {
        stat->ForDecl.e1 = create_placeholder();
      } else {
        stat->ForDecl.e1 = parse_expression(p);

        if (!match_token(p, TOK_SEMICOL)) {
          assert(0);
        }
      }

      if (match_token(p, TOK_RPAREN)) {
        stat->ForDecl.e2 = NULL;
      } else {
        stat->ForDecl.e2 = parse_expression(p);

        if (!match_token(p, TOK_RPAREN)) {
          assert(0);
        }
      }

      stat->ForDecl.stat = parse_statement(p);
    } else {
      stat->kind = STAT_FOR;

      if (match_token(p, TOK_SEMICOL)) {
        stat->For.e1 = NULL;
      } else {
        stat->For.e1 = parse_expression(p);

        if (!match_token(p, TOK_SEMICOL)) {
          assert(0);
        }
      }

      if (match_token(p, TOK_SEMICOL)) {
        stat->For.e2 = create_placeholder();
      } else {
        stat->For.e2 = parse_expression(p);

        if (!match_token(p, TOK_SEMICOL)) {
          assert(0);
        }
      }

      if (match_token(p, TOK_RPAREN)) {
        stat->For.e3 = NULL;
      } else {
        stat->For.e3 = parse_expression(p);

        if (!match_token(p, TOK_RPAREN)) {
          assert(0);
        }
      }

      stat->For.stat = parse_statement(p);
    }
  } else if (match_token(p, TOK_BREAKKEY)) {
    stat->kind = STAT_BREAK;

    if (!match_token(p, TOK_SEMICOL)) {
      assert(0);
    }
  } else if (match_token(p, TOK_CONTKEY)) {
    stat->kind = STAT_CONT;

    if (!match_token(p, TOK_SEMICOL)) {
      assert(0);
    }
  } else if (match_token(p, TOK_WHILEKEY)) {
    stat->kind = STAT_WHILE;
    
    if (!match_token(p, TOK_LPAREN)) {
      assert(0);
    }

    stat->While.exp = parse_expression(p);

    if (!match_token(p, TOK_RPAREN)) {
      assert(0);
    }

    stat->While.stat = parse_statement(p);
  } else if (match_token(p, TOK_DOKEY)) {
    stat->kind = STAT_DO;

    stat->Do.stat = parse_statement(p);

    if (!match_token(p, TOK_WHILEKEY)) {
      assert(0);
    }

    if (!match_token(p, TOK_LPAREN)) {
      assert(0);
    }

    stat->Do.exp = parse_expression(p);

    if (!match_token(p, TOK_RPAREN)) {
      assert(0);
    }

    if (!match_token(p, TOK_SEMICOL)) {
      assert(0);
    }
  } else {
    stat->kind = STAT_EXP;

    if (match_token(p, TOK_SEMICOL)) {
      stat->Expression = NULL;
    } else {
      stat->Expression = parse_expression(p);
      
      if (!match_token(p, TOK_SEMICOL)) {
        assert(0);
      }
    }
  }

  return stat;
}

AST_Declaration *parse_declaration(Parser *p) {
  AST_Declaration *dec = malloc(sizeof(AST_Declaration));

  if (match_token(p, TOK_INTKEY)) {
    if (compare_kind(p, TOK_ID)) {
      dec->name = get_token(p).literal;
      advance(p);
    } else {
      assert(0);
    }

    if (match_token(p, TOK_ASSIGN)) {
      dec->optional_exp = parse_expression(p);
    } else {
      dec->optional_exp = NULL;
    }

    if (!match_token(p, TOK_SEMICOL)) {
      assert(0);
    }
  } else {
    assert(0);
  }

  return dec;
}

int parse_block_item(Parser *p, BlockArray *arr) {
  AST_BlockItem *block = malloc(sizeof(AST_BlockItem));

  if (compare_kind(p, TOK_INTKEY)) {
    block->kind = BLOCK_DECLARE;
    block->dec = parse_declaration(p);
  } else {
    block->kind = BLOCK_STAT;
    block->stat = parse_statement(p);
  }

  push_back_block(arr, block);

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
  func->body = initialize_block_array(1);

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
    int status = parse_block_item(p, func->body);

    if (!status) {
      return 0;
    }
  }

  if (!match_token(p, TOK_RCURLY)) {
    return 0;
  }

  return 1;
}