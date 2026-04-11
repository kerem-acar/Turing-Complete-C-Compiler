typedef struct AST_Expression {
  int kind; 

  union {
    struct {
      Token op;
      struct AST_Expression *exp;
    } UnOp;

    char *Constant;
  };
} AST_Expression;

typedef struct AST_Statement {
  AST_Expression *exp;
} AST_Statement;

typedef struct AST_Function {
  AST_Statement *body;
  char *name;
} AST_Function;

typedef struct AST_Program {
  AST_Function *func;
} AST_Program;