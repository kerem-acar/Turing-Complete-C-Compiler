#ifndef LEXER_HPP
#define LEXER_HPP

#include <cctype>
#include <fstream>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>


std::vector<std::string> Lex(const std::string& file_path);

#endif
