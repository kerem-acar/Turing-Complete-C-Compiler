typedef struct AST_Function {
  StatArray *body;
  char *name;
} AST_Function;

typedef struct AST_Program {
  AST_Function *func;
} AST_Program;