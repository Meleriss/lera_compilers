#ifndef NELSE_H
#define NELSE_H

#include "NStatement.h"
#include "NBlock.h"
#include <fstream>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NElse : public NStatement
{
private:
  NBlock *body;
public:
  NElse(NBlock*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual Value* codeGen(CodeGenContext&);
  virtual ~NElse();
};

#endif