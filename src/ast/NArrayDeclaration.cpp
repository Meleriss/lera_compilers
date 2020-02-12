#include "../../include/NArrayDeclaration.h"
#include "../../include/NIdentifier.h"
#include "../../include/NInteger.h"

#include <llvm-6.0/llvm/IR/DerivedTypes.h>
#include <llvm-6.0/llvm/IR/Instructions.h>

NArrayDeclaration::NArrayDeclaration(NIdentifier *id, NInteger *size) :
                 type(NULL), id(id), size(size) {  }

void NArrayDeclaration::setType(NIdentifier *type)
{
  this->type = type;
}

void NArrayDeclaration::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"array\\n"
         << type->getName() << " "
         << id->getName() << "\"]\n";
  
  createConnect(output, idParent);

  if (size) size->toGv(output, getIdNode());
}

Value* NArrayDeclaration::codeGen(CodeGenContext& context)
{
  ArrayType *arrayType = ArrayType::get(this->type->getType(context),
                                        this->size->getValue());
  
  AllocaInst *alloc = new AllocaInst(arrayType, 0,
                                     (id->getName() + ".addr").c_str(),
                                     context.currentBlock());

  context.locals()[id->getName()] = alloc;

  alloc->setAlignment(4);
}

NArrayDeclaration::~NArrayDeclaration()
{
  if (type)
    delete type;
  
  if (id)
    delete id;
  
  if (size)
    delete size;
}