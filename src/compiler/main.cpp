#include <iostream>
#include "lexer.h" 
#include <fstream>

using namespace pellscript;

std::string read_string_from_file(const std::string &file_path) {
  const std::ifstream input_stream(file_path, std::ios_base::binary);

  if (input_stream.fail()) {
    throw std::runtime_error("Failed to open file");
  }

  std::stringstream buffer;
  buffer << input_stream.rdbuf();

  return buffer.str();
}

int main(int argc, char* argv[]) {
  std::string contents = read_string_from_file("examples/test.txt");
  std::vector<Token> tokens;
  Lexer lexer(contents);
  lexer.lex(tokens);

  for(Token& token : tokens) {
    std::cout << token.text << std::endl;
  }

  return 0;
}