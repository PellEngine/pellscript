#ifndef _COMPILER_LEXER_H_
#define _COMPILER_LEXER_H_

#include <string>
#include <vector>
#include <ctype.h>
#include <sstream>

namespace pellscript {

enum TokenType {
  NUMBER,
  IDENTIFIER,
  LPAREN,
  RPAREN,
  PLUS,
  MINUS,
  MULT,
  DIV,
  MOD,
  SEMICOLON,
  LBRACE,
  RBRACE,
  IF,
  ELIF,
  ELSE,
  DEQ,
  EQ,
  FN,
  DEFN,
  PRIMITIVE_TYPE
};

class Token {
 public:
  enum TokenType type;
  std::string text;
  int startOffset;
  int endOffset;
  int lineNumber;
};

class Lexer {
 public:
  Lexer(std::string& code);
  void lex(std::vector<Token>& tokens);

 private:
  std::string& code;
  int position = 0;
  int lineNumber;
  char peek(int n=0);
  char get();
  bool empty();
  bool isPrimitiveType(std::string& str) {
    return str == "byte" || str == "short" || str == "int" || str == "long" || str == "float" || str == "double" || str == "boolean" || str == "char";
  }
  void pushTrivialToken(TokenType type, std::vector<Token>& tokens) {
    tokens.push_back(Token{
      .type = type,
      .text = std::string(1, peek()),
      .startOffset = position,
      .endOffset = position,
      .lineNumber = lineNumber
    });
    get();
  }
  std::string substr(std::string& str, int start, int end) {
    return str.substr(start, end - start);
  }

  void readNumber(std::vector<Token>& tokens);
  void readIdentifier(std::vector<Token>& tokens);
  void readDivOrComment(std::vector<Token>& tokens);
  void readDeq(std::vector<Token>& tokens);
  void readDefn(std::vector<Token>& tokens);
};

}

#endif