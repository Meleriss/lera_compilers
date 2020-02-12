#include "../../include/NOutputStr.h"

#include <llvm-6.0/llvm/IR/IRBuilder.h>
#include <llvm-6.0/llvm/IR/Type.h>
#include <llvm-6.0/llvm/ADT/ArrayRef.h>
#include <llvm-6.0/llvm/IR/DerivedTypes.h>
#include <llvm-6.0/llvm/IR/Constant.h>

NOutputStr::NOutputStr() { }

NOutputStr::NOutputStr(const std::string &literal) : literal(literal)
{
  char_str = (char *) malloc(sizeof(char) * (literal.length() - 1));

  strncpy(char_str, literal.c_str() + 1, literal.length() - 1);

  char_str[literal.length() - 2] = '\0';
}

void NOutputStr::toGv(std::ofstream &output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"output string"
         << "\\n" << char_str << "\"]\n";
  
  createConnect(output, idParent);
}

Value *NOutputStr::codeGen(CodeGenContext &context)
{
  IRBuilder<> builder(context.currentBlock());

  Value *outString = builder.CreateGlobalStringPtr(std::string(char_str));

  std::vector<Type *> putsArgs;
  putsArgs.push_back(builder.getInt8Ty()->getPointerTo());

  ArrayRef<Type *> argsRef(putsArgs);

  FunctionType *putsType = FunctionType::get(builder.getInt32Ty(), argsRef, false);
  Constant *putsFunc = context.getModule()->getOrInsertFunction("outputStr", putsType);

  builder.CreateCall(putsFunc, outString);
}

NOutputStr::~NOutputStr()
{
  if (char_str)
    free(char_str);
}