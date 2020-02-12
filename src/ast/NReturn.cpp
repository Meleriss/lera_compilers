#include "../../include/NReturn.h"
#include <iostream>

#include <llvm-6.0/llvm/IR/Instructions.h>

NReturn::NReturn(NExpression *expr) : expr(expr) {}

void NReturn::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"return\"]\n";
  
  createConnect(output, idParent);

  if (expr)
    expr->toGv(output, getIdNode());
}

Value* NReturn::codeGen(CodeGenContext& context)
{
  ReturnInst::Create(context.getModule()->getContext(),
                     expr->codeGen(context), context.currentBlock());
}

NReturn::~NReturn()
{
  delete expr;
}