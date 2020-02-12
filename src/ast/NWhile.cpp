#include "../../include/NWhile.h"
#include "../../include/NIdentifier.h"
#include <iostream>

#include <llvm-6.0/llvm/IR/IRBuilder.h>

NWhile::NWhile(NExpression *cond, NBlock *body) : cond(cond), body(body) {}

void NWhile::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"while\"]\n";
  
  createConnect(output, idParent);

  if (cond)
    cond->toGv(output, getIdNode());
  
  if (body)
    body->toGv(output, getIdNode());
}

llvm::Value* NWhile::codeGen(CodeGenContext& context)
{
  std::map<std::string, Value *> currLocals = context.locals();

  BasicBlock *loopHeader = BasicBlock::Create(context.getContext(),
                                      "header_loop",
                                      context.currentBlock()->getParent());

  BasicBlock *loopBody = BasicBlock::Create(context.getContext(),
                                      "loop_body",
                                      context.currentBlock()->getParent());
  
  BasicBlock *loopAfter = BasicBlock::Create(context.getContext(),
                                      "loop_after",
                                      context.currentBlock()->getParent());

  IRBuilder<> builder(context.currentBlock());

  builder.CreateBr(loopHeader);

  // loopHeader
  
  context.popBlock(); // конец базового ьлока, с которым
                      // мы залетели в функцию
  context.pushBlock(loopHeader);
  context.setLocals(currLocals);

  IRBuilder<> builderHeader(context.currentBlock());

  Value *comparison = cond->codeGen(context);
  Value *zero = ConstantInt::get(Type::getInt32Ty(context.getContext()), 0, true);
  Value *cellValIsZero = builderHeader.CreateICmpNE(comparison, zero);

  builderHeader.CreateCondBr(cellValIsZero, loopBody, loopAfter);

  // end loopHeader

  // loopBody

  context.pushBlock(loopBody); // start then
  context.setLocals(currLocals);
  
  body->codeGen(context);
  
  IRBuilder<> builderBody(context.currentBlock());
  builderBody.CreateBr(loopHeader);
  
  context.popBlock(); // end then

  // end loopBody

  // loopAfter

  context.popBlock();

  context.pushBlock(loopAfter);   // продолжение базового блока,
  context.setLocals(currLocals);  // с которым мы залетели в функцию
}

NWhile::~NWhile()
{
  if (cond)
    delete cond;
  
  if (body) {
    body->free_ops();
    delete body;
  }
}