#ifndef NOUTPUTCHAR_H
#define NOUTPUTCHAR_H

#include "NStatement.h"
#include "NExpression.h"

#include <string>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NOutputChar : public NStatement
{
private:
  NExpression *expr;
public:
  NOutputChar();
  NOutputChar(NExpression *expr);
  virtual void toGv(std::ofstream &, int idParent = 0);
  virtual Value *codeGen(CodeGenContext &);
  virtual ~NOutputChar();
};

#endif