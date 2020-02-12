#include "../../include/NVarDec.h"
#include "../../include/NAssignment.h"

#include <llvm-6.0/llvm/IR/Instructions.h>

using namespace llvm;

NVarDec::NVarDec(NIdentifier *id, NExpression *assignmentExpr) :
                 type(NULL), id(id), assignmentExpr(assignmentExpr) {  }

NVarDec::NVarDec(NIdentifier *type, NIdentifier *id) :
                 type(type), id(id), assignmentExpr(NULL) { }

void NVarDec::setType(NIdentifier *type)
{
  this->type = type;
}

Type *NVarDec::getType(CodeGenContext& context)
{
  return type->getType(context);
}

std::string NVarDec::getName()
{
  return id->getName();
}

void NVarDec::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"var\\n"
         << type->getName() << " "
         << id->getName() << "\"]\n";
  
  createConnect(output, idParent);

  if (assignmentExpr)
    assignmentExpr->toGv(output, getIdNode());
}

llvm::Value* NVarDec::codeGen(CodeGenContext& context)
{
  AllocaInst *alloc = new AllocaInst(type->getType(context),
                                     0, (id->getName() + ".addr").c_str(),
                                     context.currentBlock());
  #if 0
  // normal alignment in the future (no)
  if (this->type->getName() == "int")
    alloc->setAlignment(4);
  else if (this->type->getName() == "char") {
    alloc->setAlignment(1);
  }
  #else
  alloc->setAlignment(4);
  #endif
  
  context.locals()[id->getName()] = alloc;

  if (assignmentExpr != NULL) {
    NAssignment *tmp = dynamic_cast<NAssignment*>(assignmentExpr);
    if (tmp) {
      // NAssignment assn(id, tmp->getRhs());
      // Sorry this memory leak
      NAssignment *assn = new NAssignment(id, tmp->getRhs());
      assn->codeGen(context);
    } else {
      std::cerr << "Error: [NVarDec] dynamic_cast<NAssignment*>";
      exit(EXIT_FAILURE);
    }
  }
}

NVarDec::~NVarDec()
{
  if (type)
    delete type;
  if (id)
    delete id;
  if (assignmentExpr)
    delete assignmentExpr;
}