#ifndef NSTMTEXPR_H
#define NSTMTEXPR_H

#include "NStatement.h"
#include "NExpression.h"

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NStmtExpr : public NExpression
{
private:
  NStatement *stmt;
public:
  NStmtExpr(NStatement *stmt);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NStmtExpr();
};

#endif