#include "../../include/NStmtExpr.h"

NStmtExpr::NStmtExpr(NStatement *stmt) : stmt(stmt) { }

void NStmtExpr::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"expr stmt\"]\n";
  
  createConnect(output, idParent);
  
  stmt->toGv(output, getIdNode());
}

llvm::Value* NStmtExpr::codeGen(CodeGenContext& context)
{
}

NStmtExpr::~NStmtExpr()
{
  delete stmt;
}