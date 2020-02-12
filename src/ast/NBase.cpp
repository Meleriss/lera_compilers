#include "../../include/NBase.h"

#include "llvm-6.0/llvm/Support/Errc.h"

NBase::NBase()
{
  static int countNode = 0;
  idNode = countNode++;
}

void NBase::createConnect(std::ofstream& output, int idParent)
{
  output << "\t\"node" << idParent << "\""
         << " -> "
         << "\"node" << getIdNode() << "\"\n";
}

int NBase::getIdNode() { return idNode; }

llvm::LLVMContext& NBase::myGetGlobalContext()
{
  static llvm::LLVMContext myContext;
  return myContext;
}

llvm::Value* NBase::ErrorV(const char *str)
{
  fprintf(stderr, "Error: %s\n", str);
  return 0;
}