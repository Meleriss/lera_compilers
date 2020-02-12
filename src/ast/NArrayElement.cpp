#include "../../include/NArrayElement.h"

#include <llvm-6.0/llvm/IR/Instructions.h>
#include <llvm-6.0/llvm/IR/Constants.h>

NArrayElement::NArrayElement(NInteger *element) : element(element) { }

void NArrayElement::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"array element"
         << "\\n" << getName()
         << "[" << element->getValue() << "]"
         << "\"]\n";
  
  createConnect(output, idParent);
}

Value *NArrayElement::getElementPtrInst(CodeGenContext &context)
{
  if (context.locals().find(getName()) == context.locals().end()) {
      std::cerr << "undeclared variable " << getName() << std::endl;
      return NULL;
  }
  
  std::vector<llvm::Value*> vect;

  vect.push_back(ConstantInt::get(Type::getInt32Ty(context.getContext()), 0));
  vect.push_back(ConstantInt::get(Type::getInt32Ty(context.getContext()), 
                                  element->getValue()));
  
  GetElementPtrInst *elemPtr =
    GetElementPtrInst::CreateInBounds(context.locals()[getName()],
                                      vect, "", context.currentBlock());

  return elemPtr;
}

Value* NArrayElement::codeGen(CodeGenContext& context)
{
  LoadInst *ld = new LoadInst(getElementPtrInst(context),
                              "", false, context.currentBlock());
  ld->setAlignment(4);

  return ld;
}

Value *NArrayElement::store(NExpression *rhs, CodeGenContext &context)
{
  StoreInst *st = new StoreInst(rhs->codeGen(context),
                                getElementPtrInst(context),
                                false, context.currentBlock());

  #if 0
  // normal alignment in the future (no)
  // context.locals()[lhs->getName()];
  #else
  st->setAlignment(4);
  #endif

  return st;
}

NArrayElement::~NArrayElement()
{
  // if (id)
  //   delete id;
  
  if (element)
    delete element;
}