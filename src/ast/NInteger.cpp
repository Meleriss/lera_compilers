#include "../../include/NInteger.h"

#include "llvm-6.0/llvm/IR/Constants.h"

using namespace llvm;

NInteger::NInteger(int value) : value(value) { }

int NInteger::getValue() { return value; }

void NInteger::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"integer"
         << "\\n" << value << "\"]\n";
  
  createConnect(output, idParent);
}

llvm::Value* NInteger::codeGen(CodeGenContext& context)
{
  return ConstantInt::get(Type::getInt32Ty(context.getContext()), value, true);
}

NInteger::~NInteger() { }