#ifndef NLITERAL_H
#define NLITERAL_H

#include "NExpression.h"

#include <string>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NLiteral : public NExpression
{
private:
  std::string literal;
  char *charLiteral;
public:
  NLiteral(const std::string &);
  char *getCharLiteral();
  virtual void toGv(std::ofstream &, int idParent = 0);
  virtual Value *codeGen(CodeGenContext &);
  virtual ~NLiteral();
};

NLiteral::NLiteral(const std::string &literal) : literal(literal)
{
  charLiteral = (char *) malloc(sizeof(char) * (literal.length() - 1));

  strncpy(charLiteral, literal.c_str() + 1, literal.length() - 1);

  charLiteral[literal.length() - 2] = '\0';
}

char *NLiteral::getCharLiteral()
{
  return charLiteral;
}

void NLiteral::toGv(std::ofstream &output, int idParent)
{

}

Value *NLiteral::codeGen(CodeGenContext &context)
{

}

NLiteral::~NLiteral()
{
  if (charLiteral)
    free(charLiteral);
}

#endif