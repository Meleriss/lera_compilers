#ifndef NFUNCDEC_H
#define NFUNCDEC_H

#include "NStatement.h"
#include "NIdentifier.h"
#include "NVarDec.h"
#include "NBlock.h"
#include <vector>

#include "llvm-6.0/llvm/IR/Value.h"

typedef std::vector<NVarDec*> VarList;

class NFuncDec : public NStatement
{
private:
  NIdentifier *type;
  NIdentifier *name;
  VarList *varList;
  NBlock *body;
public:
  NFuncDec(NIdentifier*, NIdentifier*, VarList*, NBlock*);
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NFuncDec();
};

#endif