typedef enum ExpKind {
  EXP_BIN_OP,
  EXP_UN_OP,
  EXP_CONSTANT,
  EXP_ASSIGN,
  EXP_REF
} ExpKind;

typedef enum StatKind {
  STAT_RETURN,
  STAT_DECLARE,
  STAT_EXP
} StatKind;

typedef struct AST_Expression {
  ExpKind kind; 

  union {
    struct {
      char *name;
      struct AST_Expression *exp;
    } Assign;

    char *Reference;

    struct {
      Token bin_op;
      struct AST_Expression *left_exp;
      struct AST_Expression *right_exp;      
    } BinOp;

    struct {
      Token un_op;
      struct AST_Expression *exp;
    } UnOp;

    char *Constant;
  };
} AST_Expression;

typedef struct AST_Statement {
  StatKind kind;
  
  union {
    AST_Expression *Return;

    struct {
      char *name;
      struct AST_Expression *exp;
    } Declare;

    AST_Expression *Expression;
  };  
} AST_Statement;

#include "../C_array/statement_array.c"

typedef struct AST_Function {
  StatArray *body;
  char *name;
} AST_Function;

typedef struct AST_Program {
  AST_Function *func;
} AST_Program;