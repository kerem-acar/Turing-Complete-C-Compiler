#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

bool Lex(const std::string &file_path, std::vector<Token> &result);

#endif
