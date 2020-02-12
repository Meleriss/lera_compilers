#include "../../include/NIf.h"
#include "../../include/NBlock.h"
#include "../../include/NExpression.h"
#include "../../include/NElse.h"
#include <iostream>
#include <fstream>

#include <llvm-6.0/llvm/IR/IRBuilder.h>

NIf::NIf(NExpression *cond, NBlock *body, NElse *_else) :
         cond(cond), body(body), _else(_else) { }

void NIf::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"if\"]\n";
  
  createConnect(output, idParent);

  if (cond)
    cond->toGv(output, getIdNode());
  
  if (body)
    body->toGv(output, getIdNode());
  
  if (_else)
    _else->toGv(output, getIdNode());
}

Value* NIf::codeGen(CodeGenContext& context)
{
  BasicBlock *then = BasicBlock::Create(context.getContext(),
                                        "",
                                        context.currentBlock()->getParent());
  
  BasicBlock *cond_false = BasicBlock::Create(context.getContext(),
                                          "",
                                          context.currentBlock()->getParent());

  IRBuilder<> builder(context.currentBlock());
  
  Value *comparison = cond->codeGen(context);
  Value *zero = ConstantInt::get(Type::getInt32Ty(context.getContext()), 0, true);
  Value *cellValIsZero = builder.CreateICmpNE(comparison, zero);
  
  builder.CreateCondBr(cellValIsZero, then, cond_false);

  std::map<std::string, Value *> currLocals = context.locals();

  context.pushBlock(then); // start then
  context.setLocals(currLocals);
  
  body->codeGen(context);
  
  IRBuilder<> builder2(context.currentBlock());
  builder2.CreateBr(cond_false);
  
  context.popBlock(); // end then

  context.popBlock(); // конец базового ьлока, с которым
                      // мы залетели в функцию
  
  context.pushBlock(cond_false); // продолжение базового блока,
  context.setLocals(currLocals); // с которым мы залетели в функцию
  
  // не выгружаю блок он остается в стеке

  // if (_else) {
  //   context.pushBlock(cond_false);
  //   _else->codeGen(context);
  //   context.popBlock();
  // }
}

NIf::~NIf()
{
  if (cond)
    delete cond;
  
  if (body) {
    body->free_ops();
    delete body;
  }
  
  if (_else)
    delete _else;
}
