#include "../../include/NBinOper.h"
#include <string>

#include <llvm-6.0/llvm/IR/Instruction.h>
#include <llvm-6.0/llvm/IR/InstrTypes.h>
#include <llvm-6.0/llvm/IR/TypeBuilder.h>
#include <llvm-6.0/llvm/IR/IRBuilder.h>

NBinOper::NBinOper() { }

NBinOper::NBinOper(std::string& op, NExpression *rhs) :
                   lhs(NULL), op(op), rhs(rhs) { }

NBinOper::NBinOper(NExpression *lhs, std::string& op, NExpression *rhs) :
                   lhs(lhs), rhs(rhs), op(op) { }

void NBinOper::setLhs(NExpression *lhs)
{
  this->lhs = lhs;
}

void NBinOper::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"" << op << "\"]\n";
  
  createConnect(output, idParent);
  
  if (lhs)
    lhs->toGv(output, getIdNode());
  
  if (rhs)
    rhs->toGv(output, getIdNode());
}

Value* NBinOper::codeGen(CodeGenContext& context)
{
  Instruction::BinaryOps instr;

  Value *l = lhs->codeGen(context);
  Value *r = rhs->codeGen(context);

  IRBuilder<> builder(context.currentBlock());

  if (op == std::string("+"))
    return builder.CreateAdd(l, r, "tmp");
  else if (op == std::string("-"))
    return builder.CreateSub(l, r, "tmp");
  else if (op == std::string("*"))
    return builder.CreateMul(l, r, "tmp");
  else if (op == std::string("/"))
    return builder.CreateSDiv(l, r, "tmp");
  else if (op == std::string("=="))
    return builder.CreateIntCast(builder.CreateICmpEQ(l, r, "tmp"),
                                 builder.getInt32Ty(), false, "");
  else if (op == std::string("!="))
    return builder.CreateIntCast(builder.CreateICmpNE(l, r, "tmp"),
                                 builder.getInt32Ty(), false, "");
  else if (op == std::string("<"))
    return builder.CreateIntCast(builder.CreateICmpSLT(l, r, "tmp"),
                                 builder.getInt32Ty(), false, "");
  else if (op == std::string("<="))
    return builder.CreateIntCast(builder.CreateICmpSLE(l, r, "tmp"),
                                 builder.getInt32Ty(), false, "");
  else if (op == std::string(">"))
    return builder.CreateIntCast(builder.CreateICmpSGT(l, r, "tmp"),
                                 builder.getInt32Ty(), false, "");
  else if (op == std::string(">="))
    return builder.CreateIntCast(builder.CreateICmpSGE(l, r, "tmp"),
                                 builder.getInt32Ty(), false, "");
  
  return NULL;
}

NBinOper::~NBinOper()
{
  delete lhs;
  delete rhs;
}