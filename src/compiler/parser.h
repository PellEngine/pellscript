#ifndef _PELLSCRIPT_PARSER_H_
#define _PELLSCRIPT_PARSER_H_

#include <vector>
#include "lexer.h"
#include "ast_nodes.h"

namespace pellscript {

class Parser {
 public:
  Parser(std::vector<Token>& tokens);
  StatementNode parse();

 private:
  std::vector<Token>& tokens;
  int position = 0;
  bool empty();
  Token& peek(int n=0);
  Token& get();
  bool requireExistance(int n);

  StatementNode readStatement();
  void readExpression(bool group);
  void readTerm();
  void readPrimary();
};

}

#endif