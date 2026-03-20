#include "ast.c"
#include "../lexer/lex.c"

Expression parse_expression(IntArray *arr) {
    assert(arr != NULL);
    assert(arr->array != NULL);

    Expression exp;

    for (int i = 0; i < arr->size; i++) {
        if (arr->array[i].type == IntegerLiteral) {
            exp.constant = arr->array[i].literal;
        }
    }

    return exp;
}


Return parse_return(IntArray *arr) {
    assert(arr != NULL);
    assert(arr->array != NULL);

    Return ret;

    for (int i = 0; i < arr->size; i++) {
        if (arr->array[i].type == ReturnKeyword) {
            ret.exp = parse_expression(arr);
        }
    }

    return ret;
}

Statement parse_statement(IntArray *arr) {
    assert(arr != NULL);
    assert(arr->array != NULL);

    Statement stat;

    stat.ret = parse_return(arr);

    return stat;
}

Function parse_function(IntArray *arr) {
    assert(arr != NULL);
    assert(arr->array != NULL);

    Function func;

    func.stat = parse_statement(arr);
    for (int i = 0; i < arr->size; i++) {
        if (arr->array[i].type == Identifier) {
            func.name = "main";
        }
    }

    return func;
}

FunctionDeclaration parse_function_declaration(IntArray *arr) {
    assert(arr != NULL);
    assert(arr->array != NULL);

    FunctionDeclaration func_dec;
    for (int i = 0; i < arr->size; i++) {
        if (arr->array[i].type == IntKeyword) {
            func_dec.func = parse_function(arr);
        }
    }

    return func_dec;
}

Program parse_program(IntArray *arr) {
    assert(arr != NULL);
    assert(arr->array != NULL);

    Program prog;

    prog.func_dec = parse_function_declaration(arr);

    return prog;
}
