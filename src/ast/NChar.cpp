#include "../../include/NChar.h"

#include "llvm-6.0/llvm/IR/Constants.h"

NChar::NChar(char value) : value(value) { }

void NChar::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"char"
         << "\\n" << value << "\"]\n";
  
  createConnect(output, idParent);
}

llvm::Value* NChar::codeGen(CodeGenContext& context)
{
  return ConstantInt::get(Type::getInt8Ty(context.getContext()), value, true);
}

NChar::~NChar() { }