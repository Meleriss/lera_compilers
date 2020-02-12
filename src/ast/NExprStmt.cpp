#include "../../include/NExprStmt.h"

NExprStmt::NExprStmt(NExpression *expr) : expr(expr) { }

void NExprStmt::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"expr stmt\"]\n";
  
  createConnect(output, idParent);
  
  expr->toGv(output, getIdNode());
}

llvm::Value* NExprStmt::codeGen(CodeGenContext& context)
{
  expr->codeGen(context);
}

NExprStmt::~NExprStmt()
{
  delete expr;
}