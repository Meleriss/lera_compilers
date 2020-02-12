#ifndef CODEGENBLOCK_H
#define CODEGENBLOCK_H

#include <llvm-6.0/llvm/IR/BasicBlock.h>
#include <llvm-6.0/llvm/IR/Value.h>

#include <map>
#include <string>

using namespace llvm;

class CodeGenBlock
{
private:
  BasicBlock *block;
  std::map<std::string, Value*> locals;
public:
  CodeGenBlock();
  void setBlock(BasicBlock*);
  std::map<std::string, Value*>& getLocals();
  void setLocals(std::map<std::string, Value *> &);
  BasicBlock *getBlock();
  ~CodeGenBlock();
};

#endif