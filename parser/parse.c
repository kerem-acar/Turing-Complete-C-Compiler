typedef struct Expression {
    int constant;
} Expression;

typedef struct Return {
    Expression exp;
} Return;

typedef struct Statement {
    Return ret;
} Statement;

typedef struct Function {
    Statement stat;
    char *name;
} Function;

typedef struct FunctionDeclaration {
    Function func;
} FunctionDeclaration;


typedef struct Program {
    FunctionDeclaration func_dec;
} Program;