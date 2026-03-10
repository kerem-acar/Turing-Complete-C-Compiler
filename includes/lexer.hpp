#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

bool Lex(const std::string& file_path, std::vector<Token>& result);

#endif
