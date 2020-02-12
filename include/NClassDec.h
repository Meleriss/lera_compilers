#ifndef NCLASSDEC_H
#define NCLASSDEC_H

#include "NStatement.h"
#include "NIdentifier.h"
#include "NFuncDec.h"
#include "NBlock.h"
#include <vector>
#include <fstream>

#include "llvm-6.0/llvm/IR/Value.h"

typedef std::vector<NFuncDec*> FuncList;

class NClassDec : public NStatement
{
private:
  NIdentifier *name;
  NBlock *methods;
public:
  NClassDec(NIdentifier*, NBlock*);
  NClassDec(NBlock*);
  void createGraph();
  virtual void toGv(std::ofstream&, int idParent = 0);
  void outputBox(std::ofstream&, int);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NClassDec();
};

#endif