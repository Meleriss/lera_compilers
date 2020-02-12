#ifndef NSTATEMENT_H
#define NSTATEMENT_H

#include "NBase.h"
#include <fstream>

#include "llvm-6.0/llvm/IR/Constants.h"

#include "CodeGenContext.h"

class NStatement : public NBase
{
protected:
  NStatement() {};
public:
  virtual ~NStatement() {};
  virtual void toGv(std::ofstream&, int idParent = 0) = 0;
  virtual llvm::Value* codeGen(CodeGenContext&) = 0;
};

#endif