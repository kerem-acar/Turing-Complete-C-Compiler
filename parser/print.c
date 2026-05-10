void print_indent(int indent, FILE *fp) {
  for (int i = 0; i < indent; ++i) {
    printf(" ");
    fprintf(fp, " ");
  }
}

void print_expression_node(AST_Expression *exp, int indent, FILE *fp) {
  print_indent(indent, fp);

  switch (exp->kind) {
  case EXP_CONSTANT: {
    printf("Expression (Constant: %s)\n", exp->Constant);
    fprintf(fp, "Expression (Constant: %s)\n", exp->Constant);
  } break;

  case EXP_UN_OP: {
    switch(exp->UnOp.un_op.kind) {
    case TOK_BITCOMP: {
      printf("Expression (Unary Operator: %c)\n", '~');
      fprintf(fp, "Expression (Unary Operator: %c)\n", '~');
    } break;
    case TOK_LOGNEG: {
      printf("Expression (Unary Operator: %c)\n", '!');
      fprintf(fp, "Expression (Unary Operator: %c)\n", '!');
    } break;
    case TOK_NEGATION: {
      printf("Expression (Unary Operator: %c)\n", '-');
      fprintf(fp, "Expression (Unary Operator: %c)\n", '-');
    } break;
    }
    print_expression_node(exp->UnOp.exp, indent + 2, fp);
  } break;

  case EXP_BIN_OP: {
    switch(exp->BinOp.bin_op.kind) {
    case TOK_ADD: {
      printf("Expression (Binary Operator: %c)\n", '+');
      fprintf(fp, "Expression (Binary Operator: %c)\n", '+');
    } break;
    case TOK_NEGATION: {
      printf("Expression (Binary Operator: %c)\n", '-');
      fprintf(fp, "Expression (Binary Operator: %c)\n", '-');
    } break;
    case TOK_MULTIPLY: {
      printf("Expression (Binary Operator: %c)\n", '*');
      fprintf(fp, "Expression (Binary Operator: %c)\n", '*');
    } break;
    case TOK_DIVIDE: {
      printf("Expression (Binary Operator: %c)\n", '/');
      fprintf(fp, "Expression (Binary Operator: %c)\n", '/');
    } break;
    case TOK_LOGAND: {
      printf("Expression (Binary Operator: %s)\n", "&&");
      fprintf(fp, "Expression (Binary Operator: %s)\n", "&&");
    } break;
    case TOK_LOGOR: {
      printf("Expression (Binary Operator: %s)\n", "||");
      fprintf(fp, "Expression (Binary Operator: %s)\n", "||");
    } break;
    case TOK_LOGEQ: {
      printf("Expression (Binary Operator: %s)\n", "==");
      fprintf(fp, "Expression (Binary Operator: %s)\n", "==");
    } break;
    case TOK_LOGNEQ: {
      printf("Expression (Binary Operator: %s)\n", "!=");
      fprintf(fp, "Expression (Binary Operator: %s)\n", "!=");
    } break;
    case TOK_LOGGEQ: {
      printf("Expression (Binary Operator: %s)\n", ">=");
      fprintf(fp, "Expression (Binary Operator: %s)\n", ">=");
    } break;
    case TOK_LOGLEQ: {
      printf("Expression (Binary Operator: %s)\n", "<=");
      fprintf(fp, "Expression (Binary Operator: %s)\n", "<=");
    } break;
    case TOK_LOGGE: {
      printf("Expression (Binary Operator: %c)\n", '>');
      fprintf(fp, "Expression (Binary Operator: %c)\n", '>');
    } break;
    case TOK_LOGLE: {
      printf("Expression (Binary Operator: %c)\n", '<');
      fprintf(fp, "Expression (Binary Operator: %c)\n", '<');
    } break;
    }
    
    print_expression_node(exp->BinOp.left_exp, indent + 2, fp);
    print_expression_node(exp->BinOp.right_exp, indent + 2, fp);
  } break;

  case EXP_ASSIGN: {
    printf("Assign (Variable: %s)\n", exp->Assign.name);
    fprintf(fp, "Assign (Variable: %s)\n", exp->Assign.name);

    print_expression_node(exp->Assign.exp, indent + 2, fp);
  } break;

  case EXP_REF: {
    printf("Reference (Variable: %s)\n", exp->Reference);
    fprintf(fp, "Reference (Variable: %s)\n", exp->Reference);
  } break;

  case EXP_COND: {
    printf("Conditional expression\n");
    fprintf(fp, "Conditional expression\n");

    print_expression_node(exp->CondExp.e1, indent + 2, fp);
    
    if (exp->CondExp.e2 != NULL) {
      print_expression_node(exp->CondExp.e2, indent + 2, fp);
    }

    if (exp->CondExp.e3 != NULL) {
      print_expression_node(exp->CondExp.e3, indent + 2, fp);
    }
  } break;
  }
}

void print_statement_node(AST_Statement *stat, int indent, FILE *fp) {
  print_indent(indent, fp);
  
  if (stat->kind == STAT_RETURN) {
    printf("Return statement\n");
    fprintf(fp, "Return statement\n");

    print_expression_node(stat->Return, indent + 2, fp);
  } else if (stat->kind == STAT_IF) {
    printf("If statement\n");
    fprintf(fp, "If statement\n");
    
    print_expression_node(stat->If.exp, indent + 2, fp);

    print_statement_node(stat->If.stat, indent + 2, fp);

    if (stat->If.optional_stat != NULL) {
      print_indent(indent, fp);
      printf("Else statement\n");
      fprintf(fp, "Else statement\n");
      print_statement_node(stat->If.optional_stat, indent + 2, fp);
    }
  } else {
    printf("Expression statement\n");
    fprintf(fp, "Expression statement\n");

    print_expression_node(stat->Expression, indent + 2, fp);
  }
}

void print_declaration_node(AST_Declaration *dec, int indent, FILE *fp) {
  print_indent(indent, fp);

  printf("Variable declaration (Name: %s)\n", dec->name);
  fprintf(fp, "Variable declaration (Name: %s)\n", dec->name);

  if (dec->optional_exp != NULL) {
    print_expression_node(dec->optional_exp, indent + 2, fp);
  } 
}

void print_function_node(AST_Function *func, int indent, FILE *fp) {
  print_indent(indent, fp);

  printf("Function (Name: %s)\n", func->name);
  fprintf(fp, "Function (Name: %s)\n", func->name);

  for (unsigned int i = 0; i < func->body->size; ++i) {
    if (func->body->array[i]->kind == BLOCK_STAT) {
      print_statement_node(func->body->array[i]->stat, indent + 2, fp);
    } else {
      print_declaration_node(func->body->array[i]->dec, indent + 2, fp);
    }
  }
}

void print_program_node(AST_Program *prog, char *result_file_path) {
  int indent = 0;

  FILE *fp = fopen(result_file_path, "w");

  printf("Program\n");
  fprintf(fp, "Program\n");

  print_function_node(prog->func, indent + 2, fp);

  fclose(fp);
}