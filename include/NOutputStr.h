#ifndef NOUTPUTSTR_H
#define NOUTPUTSTR_H

#include "NStatement.h"

#include <string>

#include "llvm-6.0/llvm/IR/Value.h"

using namespace llvm;

class NOutputStr : public NStatement
{
private:
  std::string literal;
  char *char_str;
public:
  NOutputStr();
  NOutputStr(const std::string &literal);
  virtual void toGv(std::ofstream &, int idParent = 0);
  virtual Value *codeGen(CodeGenContext &);
  virtual ~NOutputStr();
};

#endif