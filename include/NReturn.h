#ifndef NRETURN_H
#define NRETURN_H

#include "NStatement.h"
#include "NExpression.h"

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NReturn : public NStatement
{
private:
  NExpression *expr;
public:
  NReturn(NExpression*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NReturn();
};

#endif