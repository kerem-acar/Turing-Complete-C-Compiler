#include "parse.c"

void print_ast(AST_Program *prog) {
    printf("  Program\n");
    printf("    Function (Name: %s)\n", prog->func->name);
    printf("      Return statement\n");
    printf("        Expression (Constant: %s)\n",
           prog->func->body->exp->constant);
}