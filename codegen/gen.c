#include "../parser/print.c"
#include "write_to_file.c"

int generate(AST_Program *prog, char *file_path) {

    if (write_function_name_to_file(file_path, prog->func->name) == 0) {
        return 0;
    }

    if (write_return_statement(file_path, prog->func->body->exp->constant) == 0) {
        return 0;
    }

    return 1;
}