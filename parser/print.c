void print_indent(int *indent, FILE *fp) {
  for (int i = 0; i < (*indent); ++i) {
    printf(" ");
    fprintf(fp, " ");
  }
  *indent += 2;
}

void print_expression_node(AST_Expression *exp, int *indent, FILE *fp) {
  print_indent(indent, fp);

  if (exp->kind == 0) {
    printf("Expression (Constant: %s)\n", exp->Constant);
    fprintf(fp, "Expression (Constant: %s)\n", exp->Constant);
  } else {
    printf("Expression (Unary Operator: %s)\n", exp->UnOp.op.literal);
    fprintf(fp, "Expression (Unary Operator: %s)\n", exp->UnOp.op.literal);
    print_expression_node(exp->UnOp.exp, indent, fp);
  }
}

void print_statement_node(AST_Statement *stat, int *indent, FILE *fp) {
  print_indent(indent, fp);

  printf("Return statement\n");
  fprintf(fp, "Return statement\n");

  print_expression_node(stat->exp, indent, fp);
}

void print_function_node(AST_Function *func, int *indent, FILE *fp) {
  print_indent(indent, fp);

  printf("Function (Name: %s)\n", func->name);
  fprintf(fp, "Function (Name: %s)\n", func->name);

  print_statement_node(func->body, indent, fp);
}

void print_program_node(AST_Program *prog, char *result_file_path) {
  int indent = 0;

  FILE *fp = fopen(result_file_path, "w");

  printf("Program\n");
  fprintf(fp, "Program\n");

  indent += 2;

  print_function_node(prog->func, &indent, fp);

  fclose(fp);
}