#ifndef NBLOCK_H
#define NBLOCK_H

#include "NStatement.h"
#include <vector>

#include "llvm-6.0/llvm/IR/Value.h"

class NBlock : public NStatement
{
private:
  std::vector<NStatement*> ops;
public:
  NBlock();
  NBlock(NStatement*);
  NBlock(NStatement*, NStatement*);
  void append(NStatement*);
  void free_ops();
  virtual void toGv(std::ofstream&, int idParent = 0);
  virtual llvm::Value* codeGen(CodeGenContext&);
  virtual ~NBlock();
};

#endif