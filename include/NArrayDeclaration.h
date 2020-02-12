#ifndef NARRAYDECLARATION_H
#define NARRAYDECLARATION_H

#include "NStatement.h"
#include "NIdentifier.h"
#include "NInteger.h"

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NArrayDeclaration : public NStatement
{
private:
  NIdentifier *type;
  NIdentifier *id;
  NInteger *size;
public:
  NArrayDeclaration(NIdentifier*, NInteger*);
  void setType(NIdentifier*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NArrayDeclaration();
};

#endif