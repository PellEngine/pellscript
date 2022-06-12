#ifndef _PELLSCRIPT_AST_NODES_H_
#define _PELLSCRIPT_AST_NODES_H_

#include <vector>
#include <string>

namespace pellscript {

enum class StatementType {
  BLOCK,
  IF_STATEMENT,
  FUNCTION_DEF,
  VAR_DEF,
  EXPRESSION
};

class StatementNode {
 public:
  StatementNode(StatementType type) : type(type) {}
  ~StatementNode() {
    delete block;
    if(ifStatement != nullptr) {
      delete ifStatement->condition;
      delete ifStatement->trueStatement;
      delete ifStatement->elseStatement;
      delete ifStatement;
    }
    if(functionDef != nullptr) {
      delete functionDef->body;
      delete functionDef;
    }
    if(varDef != nullptr) {
      delete varDef->expression;
      delete varDef;
    }
    delete expression;
  }
  StatementType type;

  struct Block {
    std::vector<StatementNode> statements;
  };

  struct IfStatement {
    ExpressionNode* condition;
    StatementNode* trueStatement;
    std::vector<ExpressionNode> elifConditions;
    std::vector<StatementNode> elifStatements;
    StatementNode* elseStatement;
  };

  struct FunctionDef {
    std::string name;
    StatementNode* body;
  };

  struct VarDef {
    std::string name;
    ExpressionNode* expression;
  };

  Block* block;
  IfStatement* ifStatement;
  FunctionDef* functionDef;
  VarDef* varDef;
  ExpressionNode* expression;
};

}

enum class ExpressionType {
  ARITHMETIC,
  NEGATION,
  PRIMARY
};

enum class ArithmeticType {
  PLUS,
  MINUS,
  MULT,
  DIV,
  MOD
};

class ExpressionNode {
 public:
  ExpressionNode(ExpressionType type) : type(type) {}
  ~ExpressionNode() {
    if(arithmetic != nullptr) {
      delete arithmetic->left;
      delete arithmetic->right;
      delete arithmetic;
    }
    if(negation != nullptr) {
      delete negation->child;
      delete negation;
    }
    delete primary;
  }
  ExpressionType type;

  struct Arithmetic {
    ArithmeticType type;
    ExpressionNode* left;
    ExpressionNode* right;
  };

  struct Negation {
    ExpressionNode* child;
  };

  Arithmetic* arithmetic;
  Negation* negation;
  PrimaryNode* primary;
};

enum class PrimaryType {
  INT,
  FLOAT,
  IDENTIFIER,
  FN_CALL,
  GROUP
};

class PrimaryNode {
 public:
  PrimaryNode(PrimaryType type) : type(type) {}
  ~PrimaryNode() {
    delete group;
  }
  PrimaryType type;

  int intValue;
  float floatValue;
  std::string identifier;
  std::string fnCall; // TODO: struct with arguments and stuff
  ExpressionNode* group;
};

#endif