#include "lexer.h"

namespace pellscript {

Lexer::Lexer(std::string& code) : code(code) {}

bool Lexer::empty() {
  return position == code.length();
}

char Lexer::peek(int n) {
  if(position == code.length()) {
    return '\0';
  } else {
    return code.c_str()[position + n];
  }
}

char Lexer::get() {
  char currChar = code.c_str()[position];
  position++;
  return currChar;
}

void Lexer::lex(std::vector<Token>& tokens) {
  position = 0;
  lineNumber = 1;

  while(!empty()) {
    char currChar = peek();

    if(currChar == '\n') {
      lineNumber++;
    }

    if(isdigit(currChar)) {
      readNumber(tokens);
    } else if(isalpha(currChar) || currChar == '_') {
      readIdentifier(tokens);
    } else if(currChar == '(') {
      pushTrivialToken(LPAREN, tokens);
    } else if(currChar == ')') {
      pushTrivialToken(RPAREN, tokens);
    } else if(currChar == '+') {
      pushTrivialToken(PLUS, tokens);
    } else if(currChar == '-') {
      pushTrivialToken(MINUS, tokens);
    } else if(currChar == '*') {
      pushTrivialToken(MULT, tokens);
    } else if(currChar == '/') {
      readDivOrComment(tokens);
    } else if(currChar == '%') {
      pushTrivialToken(MOD, tokens);
    } else if(currChar == ';') {
      pushTrivialToken(SEMICOLON, tokens);
    } else if(currChar == '{') {
      pushTrivialToken(LBRACE, tokens);
    } else if(currChar == '}') {
      pushTrivialToken(RBRACE, tokens);
    } else if(currChar == '=') {
      readDeq(tokens);
    } else if(currChar == ':') {
      readDefn(tokens);
    } else {
      get();
    }
  }
}

void Lexer::readNumber(std::vector<Token>& tokens) {
  int startOffset = position;
  bool hadDecimalPoint = false;
  
  while(true) {
    if(isdigit(peek())) {
      get();
    } else if(peek() == '.' && !hadDecimalPoint) {
      hadDecimalPoint = true;
      get();
    } else {
      break;
    }
  }

  tokens.push_back(Token{
    .type = NUMBER,
    .text = substr(code, startOffset, position),
    .startOffset = startOffset,
    .endOffset = position,
    .lineNumber = lineNumber,
  });
}

void Lexer::readIdentifier(std::vector<Token>& tokens) {
  // Put identifier in string
  int startOffset = position;
  std::stringstream ss;
  std::string id;
  ss << get();

  while(isalpha(peek()) || isdigit(peek()) || peek() == '_') {
    ss << get();
  }
  ss >> id;

  // Check if the identifier is a keyword
  Token token{
    .text = substr(code, startOffset, position),
    .startOffset = startOffset,
    .endOffset = position,
    .lineNumber = lineNumber,
  };

  if(id == "if") {
    token.type = IF;
  } else if(id == "elif") {
    token.type = ELIF;
  } else if(id == "else") {
    token.type = ELSE;
  } else if(id == "fn") {
    token.type = FN;
  } else if(isPrimitiveType(id)) {
    token.type = PRIMITIVE_TYPE;
  } else {
    token.type = IDENTIFIER;
  }

  tokens.push_back(token);
}

void Lexer::readDivOrComment(std::vector<Token>& tokens) {
  if(peek(1) == '/') {
    get();
    get();
    while(peek() != '\n') {
      get();
    }
  } else {
    pushTrivialToken(DIV, tokens);
  }
}

void Lexer::readDeq(std::vector<Token>& tokens) {
  if(peek(1) != '=') {
    pushTrivialToken(EQ, tokens);
  } else {
    int startOffset = position;
    get();
    get();
    tokens.push_back(Token{
      .type = DEQ,
      .text = substr(code, startOffset, position),
      .startOffset = startOffset,
      .endOffset = position,
      .lineNumber = lineNumber
    });
  }
}

void Lexer::readDefn(std::vector<Token>& tokens) {
  int startOffset = position;
  get();
  if(peek() == '=') {
    get();
    tokens.push_back(Token{
      .type = DEFN,
      .text = substr(code, startOffset, position),
      .startOffset = startOffset,
      .endOffset = position,
      .lineNumber = lineNumber
    });
  } else {
    // TODO: Throw massive shit fest error on this shit.
  }
}

}