void print_indent(int indent, FILE *fp) {
  for (int i = 0; i < indent; ++i) {
    printf(" ");
    fprintf(fp, " ");
  }
}

void print_expression_node(AST_Expression *exp, int indent, FILE *fp) {
  print_indent(indent, fp);

  if (exp->kind == EXP_CONSTANT) {
    printf("Expression (Constant: %s)\n", exp->Constant);
    fprintf(fp, "Expression (Constant: %s)\n", exp->Constant);
  } else if (exp->kind == EXP_UN_OP) {
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
  } else if (exp->kind == EXP_BIN_OP) {
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
  } else if (exp->kind == EXP_ASSIGN) {
    printf("Assign (Variable: %s)\n", exp->Assign.name);
    fprintf(fp, "Assign (Variable: %s)\n", exp->Assign.name);

    print_expression_node(exp->Assign.exp, indent + 2, fp);
  } else {
    printf("Reference (Variable: %s)\n", exp->Reference.name);
    fprintf(fp, "Reference (Variable: %s)\n", exp->Reference.name);
  }
}

void print_statement_node(AST_Statement *stat, int indent, FILE *fp) {
  print_indent(indent, fp);
  
  if (stat->kind == STAT_RETURN) {
    printf("Return statement\n");
    fprintf(fp, "Return statement\n");

  print_expression_node(stat->Return.exp, indent + 2, fp);
  } else if (stat->kind == STAT_DECLARE) {
    printf("Variable declaration (Name: %s)\n", stat->Declare.name);
    fprintf(fp, "Variable declaration (Name: %s)\n", stat->Declare.name);
    
    if (stat->Declare.exp != NULL) {
      print_expression_node(stat->Declare.exp, indent + 2, fp);
    }
  } else {
    printf("Variable assignment (Name: %s)\n", stat->Expression.exp->Assign.name);
    fprintf(fp, "Variable assignment\n");

    print_expression_node(stat->Expression.exp, indent + 2, fp);
  }

}

void print_function_node(AST_Function *func, int indent, FILE *fp) {
  print_indent(indent, fp);

  printf("Function (Name: %s)\n", func->name);
  fprintf(fp, "Function (Name: %s)\n", func->name);

  for (unsigned int i = 0; i < func->body->size; ++i) {
    print_statement_node(&func->body->array[i], indent + 2, fp);
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