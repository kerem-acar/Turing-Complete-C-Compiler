void print_indent(int *indent) {
  for (int i = 0; i < (*indent); ++i) {
    printf(" ");
  }
  *indent += 2;
}

void print_expression_node(AST_Expression *exp, int *indent) {
  print_indent(indent);

  if (exp->kind == 0) {
    printf("Expression (Constant: %s)\n", exp->Constant);
  } else {
    printf("Expression (Unary Operator: %s)\n", exp->UnOp.op.literal);
    print_expression_node(exp->UnOp.exp, indent);
  }
}

void print_statement_node(AST_Statement *stat, int *indent) {
  print_indent(indent);

  printf("Return statement\n");

  print_expression_node(stat->exp, indent);
}

void print_function_node(AST_Function *func, int *indent) {
  print_indent(indent);

  printf("Function (Name: %s)\n", func->name);

  print_statement_node(func->body, indent);
}

void print_program_node(AST_Program *prog) {
  int indent = 0;

  printf("Program\n");

  indent += 2;

  print_function_node(prog->func, &indent);
}