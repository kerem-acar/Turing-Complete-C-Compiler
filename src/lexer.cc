#include "lexer.hpp"
#include "token.hpp"


const std::map<std::string, Token> kKeywordMap = {
  {"return", Token::ReturnKeyword},
  {"int", Token::IntKeyword}
};

const std::map<char, Token> kSyntaxMap = {
  {'{', Token::OpenBracket},
  {'}', Token::CloseBracket},
  {'(', Token::OpenParen},
  {')', Token::CloseParen},
  {';', Token::Semicolon}
};

std::vector<Token> Lex(const std::string& file_path) {
  std::ifstream ifs{file_path};

  std::string line;
  std::vector<Token> result;


  while (std::getline(ifs, line)) {
    for (unsigned int i = 0; i < line.size(); ++i) {
      if (std::isspace(line[i])) {
        continue;
      }
      if (kSyntaxMap.contains(line[i])) {
        result.push_back(kSyntaxMap.at(line[i]));
        continue;
      }
      if (std::isdigit(line[i])) {
        std::string number;
        unsigned int j = i;

        while (j < line.size() && std::isdigit(line[j])) {
          number += line[j];
          j++;
        }
        i = j - 1;
        result.push_back(Token::IntegerLiteral);
        continue;
      }
      if (std::isalpha(line[i])) {
        std::string word;
        unsigned int j = i;
        while (j < line.size() && std::isalpha(line[j])) {
          word += line[j];
          j++;
        }
        i = j - 1;
        if (kKeywordMap.contains(word)) {
          result.push_back(kKeywordMap.at(word));
        } else {
          result.push_back(Token::Identifier);
        }
        continue;
      }
    }
  }
  return result;
}
