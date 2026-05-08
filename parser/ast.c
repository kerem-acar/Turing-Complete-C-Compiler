typedef enum ExpKind {
  EXP_BIN_OP,
  EXP_UN_OP,
  EXP_CONSTANT,
  EXP_ASSIGN,
  EXP_REF,
  EXP_COND
} ExpKind;

typedef enum StatKind {
  STAT_RETURN,
  STAT_EXP,
  STAT_IF
} StatKind;

typedef enum BlockKind {
  BLOCK_DECLARE,
  BLOCK_STAT
} BlockKind;

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

    struct {
      struct AST_Expression *e1;
      struct AST_Expression *e2;
      struct AST_Expression *e3;
    } CondExp;

    char *Constant;
  };
} AST_Expression;

typedef struct AST_Statement {
  StatKind kind;
  
  union {
    AST_Expression *Return;

    struct {
      AST_Expression *exp;
      struct AST_Statement *stat;
      struct AST_Statement *optional_stat;
    } If;

    AST_Expression *Expression;
  };  
} AST_Statement;

typedef struct AST_Declaration {
  char *name;
  AST_Expression *optional_exp;
} AST_Declaration;

typedef struct AST_BlockItem {
  BlockKind kind;

  union {
    AST_Statement *stat;
    AST_Declaration *dec;
  };
} AST_BlockItem;

#include "../C_array/block_array.c"

typedef struct AST_Function {
  BlockArray *body;
  char *name;
} AST_Function;

typedef struct AST_Program {
  AST_Function *func;
} AST_Program;