#include "../../include/NIdentifier.h"

#include <llvm-6.0/llvm/IR/Instructions.h>

NIdentifier::NIdentifier() { }

NIdentifier::NIdentifier(const std::string& name) : name(name) { }

std::string NIdentifier::getName() { return name; }

void NIdentifier::setName(std::string name)
{
  this->name = name;
}

Type *NIdentifier::getType(CodeGenContext& context)
{
  if (name.compare("int") == 0)
    return IntegerType::get(context.getContext(), 32);
  else if (name.compare("char") == 0)
    return IntegerType::get(context.getContext(), 8);
  return Type::getVoidTy(context.getContext());
}

void NIdentifier::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"var"
         << "\\n" << name << "\"]\n";
  
  createConnect(output, idParent);
}

Value* NIdentifier::codeGen(CodeGenContext& context)
{
  if (context.locals().find(name) == context.locals().end()) {
      std::cerr << "undeclared variable " << name << std::endl;
      return NULL;
  }

  LoadInst *ld = new LoadInst(context.locals()[name], "", false, context.currentBlock());
  ld->setAlignment(4);

  return ld;
}

Value *NIdentifier::store(NExpression *rhs, CodeGenContext &context)
{
  StoreInst *st = new StoreInst(rhs->codeGen(context),
                                context.locals()[name],
                                false, context.currentBlock());
  
  #if 0
  // normal alignment in the future (no)
  // context.locals()[lhs->getName()];
  #else
  st->setAlignment(4);
  #endif

  return st;
}

NIdentifier::~NIdentifier() { }