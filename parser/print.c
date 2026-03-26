#include "parse.c"

void print_expression_node(AST_Expression *exp, int *indent) {
  for (int i = 0; i < (*indent); ++i) {
    printf(" ");
  }

  printf("Expression (Constant: %s)\n", exp->constant);

  *indent += 2;
}

void print_statement_node(AST_Statement *stat, int *indent) {
  for (int i = 0; i < (*indent); ++i) {
    printf(" ");
  }

  printf("Return statement\n");

  *indent += 2;

  print_expression_node(stat->exp, indent);
}

void print_function_node(AST_Function *func, int *indent) {
  for (int i = 0; i < (*indent); ++i) {
    printf(" ");
  }

  printf("Function (Name: %s)\n", func->name);

  *indent += 2;

  print_statement_node(func->body, indent);
}

void print_program_node(AST_Program *prog) {
  int indent = 0;

  printf("Program\n");

  indent += 2;

  print_function_node(prog->func, &indent);
}