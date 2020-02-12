#ifndef NARRAYELEMENT_H
#define NARRAYELEMENT_H

#include "NExpression.h"
#include "NIdentifier.h"
#include "NInteger.h"
#include <iostream>
#include <fstream>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NArrayElement : public NIdentifier
{
private:
  NInteger *element;
public:
  NArrayElement(NInteger*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  Value *getElementPtrInst(CodeGenContext &);
  virtual Value* codeGen(CodeGenContext&);
  virtual Value* store(NExpression *, CodeGenContext &);
  virtual ~NArrayElement();
};

#endif