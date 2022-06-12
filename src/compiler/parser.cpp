#include "parser.h"

namespace pellscript {

Parser::Parser(std::vector<Token>& tokens) : tokens(tokens) {}

bool Parser::empty() {
  return position == tokens.size();
}

bool Parser::requireExistance(int n) {
  return position < tokens.size() - n;
}

Token& Parser::peek(int n) {
  return tokens[position + n];
}

Token& Parser::get() {
  Token& token = tokens[position];
  position++;
  return token;
}

StatementNode Parser::parse() {
  StatementNode tree(StatementType::BLOCK);
  tree.block = new StatementNode::Block;

  while(!empty()) {
    tree.block->statements.push_back(readStatement());
  }

  return tree;
} 

StatementNode Parser::readStatement() {}

}