#ifndef NASSIGNMENT_H
#define NASSIGNMENT_H

#include "NExpression.h"
#include "NIdentifier.h"

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NAssignment : public NExpression
{
private:
  NIdentifier *lhs;
  NExpression *rhs;
public:
  NAssignment(NExpression*);
  NAssignment(NIdentifier*, NExpression*);
  void setLhs(NIdentifier*);
  NIdentifier* getLhs();
  NExpression* getRhs();
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NAssignment();
  // virtual llvm::Value* codeGen(CodeGenContext& context);
};

#endif