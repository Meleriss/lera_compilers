#include "../../include/NMethodCall.h"

#include <llvm-6.0/llvm/IR/Function.h>
#include <llvm-6.0/llvm/IR/Instructions.h>
#include <llvm-6.0/llvm/ADT/APInt.h>

NMethodCall::NMethodCall(ExpressionList *exprList) :
                         id(NULL), exprList(exprList){ }

NMethodCall::NMethodCall(NIdentifier *id) :
                         id(id), exprList(NULL) { }

void NMethodCall::setId(NIdentifier *id)
{
  this->id = id;
}

void NMethodCall::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"method call"
         << "\\n" << id->getName() << "\"]\n";
  
  createConnect(output, idParent);
  
  if (exprList) {
    for (auto expr : *exprList)
      if (expr)
        expr->toGv(output, getIdNode());
  }
}

Value* NMethodCall::codeGen(CodeGenContext& context)
{
  Function *function = context.getModule()->getFunction(id->getName().c_str());

  if (function == NULL) {
    std::cerr << "no such function " << id->getName() << std::endl;
  }

  std::vector<Value*> args;
  
  for (auto arg : *exprList) {
    args.push_back(arg->codeGen(context));
  }

  ArrayRef<Value*> arrRef(args);

  CallInst *call = CallInst::Create(function, arrRef, "",
                                    context.currentBlock());

  return call;
}

NMethodCall::~NMethodCall()
{
  delete id;

  if (exprList) {
    for (auto expr : *exprList)
      if (expr)
        delete expr;
    delete exprList;
  }
}