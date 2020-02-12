#ifndef NEXPRESSION_H
#define NEXPRESSION_H

#include "NBase.h"
#include <fstream>
#include "llvm-6.0/llvm/IR/Value.h"

#include "CodeGenContext.h"

class NExpression : public NBase
{
protected:
  NExpression() {};
public:
  virtual void toGv(std::ofstream&, int idParent = 0) = 0;
  virtual llvm::Value* codeGen(CodeGenContext&) = 0;
  // virtual Value *store(NExpression *, CodeGenContext &);
  virtual ~NExpression() {};
};

#endif