#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <map>

std::vector<Token> Lex(const std::string& file_path);

#endif
