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

    struct {
      char *name;
    } Reference;

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
    struct {
      struct AST_Expression *exp;
    } Return;

    struct {
      char *name;
      struct AST_Expression *exp;
    } Declare;

    struct {
      struct AST_Expression *exp;
    } Expression;

  };  
} AST_Statement;
