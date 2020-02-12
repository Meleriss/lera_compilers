#include "../../include/CodeGenContext.h"

CodeGenContext::CodeGenContext(/* args */)
{
  module = new Module("test module", llvmContext);
}

Module* CodeGenContext::getModule()
{
  return module;
}

LLVMContext& CodeGenContext::getContext()
{
  return llvmContext;
}

std::map<std::string, Value*>& CodeGenContext::locals()
{
  return blocks.top()->getLocals();
}

void CodeGenContext::setLocals(std::map<std::string, Value *> &locals)
{
  blocks.top()->setLocals(locals);
}

BasicBlock *CodeGenContext::currentBlock()
{
  return blocks.top()->getBlock();
}

void CodeGenContext::pushBlock(BasicBlock *block)
{
  blocks.push(new CodeGenBlock());
  blocks.top()->setBlock(block);
}

void CodeGenContext::popBlock()
{
  CodeGenBlock *top = blocks.top();
  blocks.pop();
  delete top;
}

CodeGenContext::~CodeGenContext()
{
}