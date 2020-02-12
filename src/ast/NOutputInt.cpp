#include "../../include/NOutputInt.h"

#include <llvm-6.0/llvm/IR/IRBuilder.h>
#include <llvm-6.0/llvm/IR/Type.h>
#include <llvm-6.0/llvm/ADT/ArrayRef.h>
#include <llvm-6.0/llvm/IR/DerivedTypes.h>
#include <llvm-6.0/llvm/IR/Constant.h>

NOutputInt::NOutputInt() { }

NOutputInt::NOutputInt(NExpression *expr) : expr(expr) { }

void NOutputInt::toGv(std::ofstream &output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"output int"
        //  << "\\n" << char_str << "\"]\n";
        << "\\n" << "value" << "\"]\n";
  
  createConnect(output, idParent);
}

Value *NOutputInt::codeGen(CodeGenContext &context)
{
  IRBuilder<> builder(context.currentBlock());

  Value *outInt = expr->codeGen(context);

  std::vector<Type *> putsArgs;
  putsArgs.push_back(builder.getInt32Ty());

  ArrayRef<Type *> argsRef(putsArgs);

  FunctionType *putsType = FunctionType::get(builder.getInt32Ty(), argsRef, false);
  Constant *putsFunc = context.getModule()->getOrInsertFunction("outputInt", putsType);

  builder.CreateCall(putsFunc, outInt);
}

NOutputInt::~NOutputInt()
{
  if (expr)
    delete(expr);
}