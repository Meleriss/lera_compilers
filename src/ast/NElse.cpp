#include "../../include/NElse.h"

NElse::NElse(NBlock *body) : body(body) { }

void NElse::toGv(std::ofstream& output, int idParent)
{
  output << "\t\"node" << getIdNode() << "\""
         << "[shape=box, label=\"else\"]\n";
  
  createConnect(output, idParent);
  
  if (body)
    body->toGv(output, getIdNode());
}

Value* NElse::codeGen(CodeGenContext& context)
{
  // body->codeGen(context);
}

NElse::~NElse()
{
  if (body) {
    body->free_ops();
    delete body;
  }
}