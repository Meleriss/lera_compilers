#include "../../include/NBlock.h"
#include <iostream>

NBlock::NBlock() {}

NBlock::NBlock(NStatement *op) { append(op); }

NBlock::NBlock(NStatement *op1, NStatement *op2)
{
  append(op1);
  append(op2);
}

void NBlock::append(NStatement *op)
{
  NBlock *block = dynamic_cast<NBlock*>(op);
  if (block) {
    for (auto op : block->ops)
      ops.push_back(op);
    delete block;
  } else if (op)
    ops.push_back(op);
}

void NBlock::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"body\"]\n";

  createConnect(output, idParent);

  for (auto op : ops)
    op->toGv(output, getIdNode());
}

llvm::Value* NBlock::codeGen(CodeGenContext& context)
{
  for (auto method : ops)
    method->codeGen(context);
}

void NBlock::free_ops()
{
  for (auto op : ops)
    delete op;
}

NBlock::~NBlock()
{
}