#ifndef NEXPRSTMT_H
#define NEXPRSTMT_H

#include "NStatement.h"
#include "NExpression.h"

#include "llvm-6.0/llvm/IR/Value.h"

class NExprStmt : public NStatement
{
private:
  NExpression *expr;
public:
  NExprStmt(NExpression *expr);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NExprStmt();
};

#endif