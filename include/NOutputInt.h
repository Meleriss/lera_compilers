#ifndef NOUTPUTINT_H
#define NOUTPUTINT_H

#include "NStatement.h"
#include "NExpression.h"

#include <string>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NOutputInt : public NStatement
{
private:
  NExpression *expr;
public:
  NOutputInt();
  NOutputInt(NExpression *);
  virtual void toGv(std::ofstream &, int idParent = 0);
  virtual Value *codeGen(CodeGenContext &);
  virtual ~NOutputInt();
};

#endif