#include "../C_stoi/stoi.c"
#include "../lexer/lex.c"
#include "print.c"

int main() {

  char *file_path1 = "../test_cases/test_case1.c";
  char *file_path2 = "../test_cases/test_case2.c";
  char *file_path3 = "../test_cases/test_case3.c";

  TokenArray *arr1 = initialize_token_array(1);
  TokenArray *arr2 = initialize_token_array(1);
  TokenArray *arr3 = initialize_token_array(1);

  const char *s1 = read_file(file_path1);
  const char *s2 = read_file(file_path2);
  const char *s3 = read_file(file_path3);

  lex(s1, arr1);
  lex(s2, arr2);
  lex(s3, arr3);

  Parser *p1 = initialize_parser(arr1);
  Parser *p2 = initialize_parser(arr2);
  Parser *p3 = initialize_parser(arr3);

  AST_Program *prog_1 = malloc(sizeof(AST_Program));
  AST_Program *prog_2 = malloc(sizeof(AST_Program));
  AST_Program *prog_3 = malloc(sizeof(AST_Program));

  int parse_one_result = parse_function(p1, prog_1);
  int parse_two_result = parse_function(p2, prog_2);
  int parse_three_result = parse_function(p3, prog_3);

  if (parse_one_result == 1) {
    print_program_node(prog_1);
    int out = 0;
    stoi(prog_1->func->body->exp->constant, &out);
    assert(out == 333);
  }

  if (parse_two_result == 1) {
    print_program_node(prog_2);
    int out = 0;
    stoi(prog_2->func->body->exp->constant, &out);
    assert(out == 42);
  }

  if (parse_three_result == 1) {
    print_program_node(prog_3);
    int out = 0;
    stoi(prog_3->func->body->exp->constant, &out);
    assert(out == 27);
  }

  return 0;
}