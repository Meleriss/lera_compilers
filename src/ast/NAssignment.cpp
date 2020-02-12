#include "../../include/NAssignment.h"

#include <llvm-6.0/llvm/IR/Instructions.h>

NAssignment::NAssignment(NExpression *rhs) : lhs(NULL), rhs(rhs) { }

NAssignment::NAssignment(NIdentifier *lhs, NExpression *rhs) :
                         lhs(lhs), rhs(rhs) { }

void NAssignment::setLhs(NIdentifier *lhs)
{
  this->lhs = lhs;
}

NIdentifier* NAssignment::getLhs()
{
  return lhs;
}

NExpression *NAssignment::getRhs()
{
  return rhs;
}

void NAssignment::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"=\"]\n";

  createConnect(output, idParent);
  
  if (lhs)
    lhs->toGv(output, getIdNode());
  
  if (rhs)
    rhs->toGv(output, getIdNode());
}

Value* NAssignment::codeGen(CodeGenContext& context)
{
  if (context.locals().find(lhs->getName()) == context.locals().end()) {
    std::cerr << "undeclared variable " << lhs->getName() << std::endl;
    return NULL;
  }

  return lhs->store(rhs, context);
}

NAssignment::~NAssignment()
{
  if (lhs)
    delete lhs;
  
  if (rhs)
    delete rhs;
}