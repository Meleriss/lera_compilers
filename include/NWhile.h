#ifndef NWHILE_H
#define NWHILE_H

#include "NStatement.h"
#include "NExpression.h"
#include "NBlock.h"

#include "llvm-6.0/llvm/IR/Value.h"

class NWhile : public NStatement
{
private:
  NExpression *cond;
  NBlock *body;
public:
  NWhile(NExpression*, NBlock*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NWhile();
};

#endif