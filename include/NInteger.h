#ifndef NINTEGER_H
#define NINTEGER_H

#include "NExpression.h"
#include "llvm-6.0/llvm/IR/Value.h"

class NInteger : public NExpression
{
private:
  int value;
public:
  NInteger(int value);
  int getValue();
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NInteger();
};

#endif