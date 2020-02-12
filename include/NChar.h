#ifndef NCHAR_H
#define NCHAR_H

#include "NExpression.h"

#include "llvm-6.0/llvm/IR/Value.h"

class NChar : public NExpression
{
private:
  char value;
public:
  NChar(char);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NChar();
};

#endif