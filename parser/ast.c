typedef struct AST_Expression AST_Expression;
typedef struct AST_Statement AST_Statement;
typedef struct AST_Declaration AST_Declaration;
typedef struct AST_BlockItem AST_BlockItem;
typedef struct AST_Function AST_Function;
typedef struct AST_Program AST_Program;

#include "../C_array/block_array.c"

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
  STAT_IF,
  STAT_COMP,
  STAT_FOR,
  STAT_FORDEC,
  STAT_WHILE,
  STAT_DO,
  STAT_BREAK,
  STAT_CONT
} StatKind;

typedef enum BlockKind {
  BLOCK_DECLARE,
  BLOCK_STAT
} BlockKind;


struct AST_Expression {
  ExpKind kind; 

  union {
    struct {
      char *name;
      AST_Expression *exp; 
    } Assign;

    char *Reference;

    struct {
      Token bin_op;
      AST_Expression *left_exp;
      AST_Expression *right_exp;      
    } BinOp;

    struct {
      Token un_op;
      AST_Expression *exp;
    } UnOp;

    struct {
      AST_Expression *e1;
      AST_Expression *e2;
      AST_Expression *e3;
    } CondExp;

    char *Constant;
  };
};

struct AST_Statement {
  StatKind kind;
  
  union {
    AST_Expression *Return;

    struct {
      AST_Expression *exp;
      AST_Statement *stat;
      AST_Statement *optional_stat;
    } If;

    AST_Expression *Expression; 

    BlockArray *Compound; 

    struct {
      AST_Expression *e1; 
      AST_Expression *e2;
      AST_Expression *e3;
      AST_Statement *stat;
    } For;

    struct {
      AST_Declaration *dec;
      AST_Expression *e1;
      AST_Expression *e2;
      AST_Statement *stat;
    } ForDecl;

    struct {
      AST_Expression *exp;
      AST_Statement *stat;
    } While;

    struct {
      AST_Statement *stat;
      AST_Expression *exp;
    } Do;
  };  
};

struct AST_Declaration {
  char *name;
  AST_Expression *optional_exp;
};

struct AST_BlockItem {
  BlockKind kind;

  union {
    AST_Statement *stat;
    AST_Declaration *dec;
  };
};

struct AST_Function {
  BlockArray *body;
  char *name;
};

struct AST_Program {
  AST_Function *func;
};