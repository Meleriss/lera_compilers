#ifndef CODEGENCONTEXT_H
#define CODEGENCONTEXT_H

#include "CodeGenBlock.h"

#include <stack>

#include <llvm-6.0/llvm/IR/Module.h>
#include <llvm-6.0/llvm/IR/LLVMContext.h>
#include <llvm-6.0/llvm/IR/TypeBuilder.h>

using namespace llvm;

class CodeGenContext
{
private:
  Module *module;
  LLVMContext llvmContext;
  std::stack<CodeGenBlock *> blocks;
public:
  CodeGenContext();
  Module *getModule();
  LLVMContext& getContext();
  std::map<std::string, Value *> &locals();
  void setLocals(std::map<std::string, Value *> &);
  BasicBlock *currentBlock();
  void pushBlock(BasicBlock *);
  void popBlock();
  ~CodeGenContext();
};

#endif