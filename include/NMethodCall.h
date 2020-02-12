#ifndef NMETHODCALL
#define NMETHODCALL

#include "NExpression.h"
#include "NIdentifier.h"
#include <vector>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

typedef std::vector<NExpression*> ExpressionList;

class NMethodCall : public NExpression
{
private:
  NIdentifier *id;
  ExpressionList *exprList;
public:
  NMethodCall(ExpressionList*);
  NMethodCall(NIdentifier*);
  void setId(NIdentifier*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NMethodCall();
};

#endif