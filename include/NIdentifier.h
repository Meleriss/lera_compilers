#ifndef NIDENTIFIER_H
#define NIDENTIFIER_H

#include "NExpression.h"
#include <string>
#include <iostream>

#include "llvm-6.0/llvm/IR/Value.h"
#include "llvm-6.0/llvm/IR/Type.h"

#include "CodeGenContext.h"

using namespace llvm;

class NIdentifier : public NExpression
{
private:
  std::string name;
public:
  NIdentifier();
  NIdentifier(const std::string& name);
  std::string getName();
  void setName(std::string);
  Type* getType(CodeGenContext&);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual Value *store(NExpression *, CodeGenContext &);
  virtual ~NIdentifier();
};

#endif