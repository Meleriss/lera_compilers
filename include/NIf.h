#ifndef NIF_H
#define NIF_H

#include "NStatement.h"
#include "NExpression.h"
#include "NBlock.h"
#include "NElse.h"

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NIf : public NStatement
{
private:
  NExpression *cond;
  NBlock *body;
  NElse *_else;
public:
  NIf(NExpression*, NBlock*, NElse*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NIf();
};

#endif