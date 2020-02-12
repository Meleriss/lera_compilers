#ifndef NBINOPER_H
#define NBINOPER_H

#include "NExpression.h"
#include <string>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NBinOper : public NExpression
{
private:
  std::string op;
  NExpression *lhs;
  NExpression *rhs;
public:
  NBinOper();
  NBinOper(std::string&, NExpression*);
  NBinOper(NExpression*, std::string&, NExpression*);
  void setLhs(NExpression*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NBinOper();
};

#endif