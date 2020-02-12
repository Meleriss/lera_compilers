#include "../../include/NFuncDec.h"
#include <iostream>

#include <llvm-6.0/llvm/IR/Function.h>
#include <llvm-6.0/llvm/IR/DerivedTypes.h>
#include <llvm-6.0/llvm/IR/IRBuilder.h>
#include <llvm-6.0/llvm/IR/BasicBlock.h>
#include <llvm-6.0/llvm/ADT/ArrayRef.h>
#include <llvm-6.0/llvm/ADT/SmallVector.h>

NFuncDec::NFuncDec(NIdentifier *type, NIdentifier *name,
                   VarList* varList, NBlock *body) :
                   type(type), name(name), varList(varList), body(body)
{
  if (name->getName() == "Main")
    name->setName("main");
}

void NFuncDec::toGv(std::ofstream& output, int idParent)
{
  // output box
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"method"
         << "\\n"
         << type->getName() << " "
         << name->getName() << "\"]\n";
  
  createConnect(output, idParent);

  // var list
  for (auto var : *varList)
    var->toGv(output, getIdNode());
  
  // body
  body->toGv(output, getIdNode());
}

Value* NFuncDec::codeGen(CodeGenContext& context)
{
  std::vector<Type*> argTypes;
  for (auto type : *varList)
    argTypes.push_back(type->getType(context));

  ArrayRef<Type*> arrRef(argTypes);

  FunctionType *funcTy = FunctionType::get(
                          type->getType(context),
                          arrRef, true);

  Function *func = Function::Create(funcTy,
                                    GlobalValue::ExternalLinkage,
                                    name->getName(),
                                    context.getModule());

  func->setCallingConv(CallingConv::C);

  BasicBlock *labelEntry = BasicBlock::Create(context.getContext(),
                                              "entry", func);

  context.pushBlock(labelEntry);

  Function::arg_iterator argBegin = func->arg_begin();
  Function::arg_iterator argEnd = func->arg_end();
  for (int i = 0; argBegin != argEnd; argBegin++, i++) {
    NVarDec *arg = varList->at(i);
    argBegin->setName(arg->getName()); // set name arg
    arg->codeGen(context);             // alloc arg

    StoreInst *st = new StoreInst(argBegin, 
                                  context.locals()[arg->getName()],
                                  false, labelEntry);
    st->setAlignment(4);
  }

  body->codeGen(context);

  context.popBlock();
}

NFuncDec::~NFuncDec()
{
  if (type)
    delete type;
  
  if (name)
    delete name;

  if (varList) {
    for (auto var : *varList)
      if (var)
        delete var;
    
    delete varList;
  }

  body->free_ops();
  delete body;
}