#include "lexer.hpp"

std::vector<std::string> Lex(const std::string& file_path) {
  std::ifstream ifs{file_path};

  if (!ifs) {
    throw std::invalid_argument("File path is invalid");
  }

  std::string line;
  std::vector<std::string> result;

  std::set<char> valid_characters = {'{', '}', '(', ')', ';'};

  while (std::getline(ifs, line)) {
    for (unsigned int i = 0; i < line.size(); ++i) {
      if (std::isspace(line[i])) {
        continue;
      }
      if (valid_characters.contains(line[i])) {
        std::string character;
        character += line[i];
        result.push_back(character);
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
        result.push_back(number);
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
        if (word == "main" || word == "return" || word == "int") {
          result.push_back(word);
        }
        continue;
      }
    }
  }
  return result;
}
