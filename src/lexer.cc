#include "lexer.hpp"
#include "token.hpp"




bool Lex(const std::string& file_path, std::vector<Token>& result) {
  std::ifstream ifs{file_path};

  if (!ifs) {
    return false;
  }
  const std::unordered_map<std::string, Token> keywordMap = {
    {"return", Token::ReturnKeyword},
    {"int", Token::IntKeyword}
  };

  const std::unordered_map<char, Token> singleCharMap = {
    {'{', Token::OpenBracket},
    {'}', Token::CloseBracket},
    {'(', Token::OpenParen},
    {')', Token::CloseParen},
    {';', Token::Semicolon}
  };


  std::string content((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());



  for (unsigned int i = 0; i < content.size(); ++i) {
    if (std::isspace(content[i])) {
      continue;
    }
    if (singleCharMap.contains(content[i])) {
      result.push_back(singleCharMap.at(content[i]));
      continue;
    }
    if (std::isdigit(content[i])) {
      std::string number;

      while (i < content.size() && std::isdigit(content[i])) {
        number += content[i];
        i++;
      }
      i--;
      result.push_back(Token::IntegerLiteral);
      continue;
    }
    if (std::isalpha(content[i])) {
      std::string word;
      while (i < content.size() && std::isalpha(content[i])) {
        word += content[i];
        i++;
      }
      i--;
      if (keywordMap.contains(word)) {
        result.push_back(keywordMap.at(word));
      } else {
        result.push_back(Token::Identifier);
      }
      continue;
    }
  }
  return true;
}

