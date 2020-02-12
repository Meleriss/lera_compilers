#ifndef NVARDEC_H
#define NVARDEC_H

#include "NStatement.h"
#include "NExpression.h"
#include "NIdentifier.h"

#include "llvm-6.0/llvm/IR/Value.h"
#include "llvm-6.0/llvm/IR/Type.h"

#include "CodeGenContext.h"

using namespace llvm;

class NVarDec : public NStatement
{
private:
  NIdentifier *type;
  NIdentifier *id;
  NExpression *assignmentExpr; // NAssingment
public:
  NVarDec(NIdentifier*, NExpression*);
  NVarDec(NIdentifier*, NIdentifier*);
  void setType(NIdentifier*);
  Type* getType(CodeGenContext&);
  std::string getName();
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NVarDec();
};

#endif