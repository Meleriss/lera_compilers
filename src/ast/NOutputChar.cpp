#include "../../include/NOutputChar.h"

#include <llvm-6.0/llvm/IR/IRBuilder.h>
#include <llvm-6.0/llvm/IR/Type.h>
#include <llvm-6.0/llvm/ADT/ArrayRef.h>
#include <llvm-6.0/llvm/IR/DerivedTypes.h>
#include <llvm-6.0/llvm/IR/Constant.h>

NOutputChar::NOutputChar() { }

NOutputChar::NOutputChar(NExpression *expr) : expr(expr) { }

void NOutputChar::toGv(std::ofstream &output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"output char\"]\n";
  
  createConnect(output, idParent);
}

Value *NOutputChar::codeGen(CodeGenContext &context)
{
  IRBuilder<> builder(context.currentBlock());

  Value *outInt = expr->codeGen(context);

  std::vector<Type *> putsArgs;
  putsArgs.push_back(builder.getInt8Ty());

  ArrayRef<Type *> argsRef(putsArgs);

  FunctionType *putsType = FunctionType::get(builder.getInt32Ty(), argsRef, false);
  Constant *putsFunc = context.getModule()->getOrInsertFunction("outputChar", putsType);

  builder.CreateCall(putsFunc, outInt);
}

NOutputChar::~NOutputChar()
{
  if (expr)
    delete(expr);
}