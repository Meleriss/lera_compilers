#include "../../include/CodeGenBlock.h"

CodeGenBlock::CodeGenBlock(/* args */)
{
}

void CodeGenBlock::setBlock(BasicBlock *block)
{
  this->block = block;
}

std::map<std::string, Value *> &CodeGenBlock::getLocals()
{
  return locals;
}

void CodeGenBlock::setLocals(std::map<std::string, Value *> &locals)
{
  this->locals = locals;
}

BasicBlock *CodeGenBlock::getBlock()
{
  return block;
}

CodeGenBlock::~CodeGenBlock()
{
}