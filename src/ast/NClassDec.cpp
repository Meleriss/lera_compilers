#include "../../include/NClassDec.h"
#include <iostream>
#include <fstream>

#include <llvm-6.0/llvm/Support/raw_ostream.h>

NClassDec::NClassDec(NIdentifier *name, NBlock *methods) :
                     name(name), methods(methods) {}

NClassDec::NClassDec(NBlock *methods) :
                     name(NULL), methods(methods) {}

void NClassDec::createGraph()
{
  std::ofstream output("graph.gv");

  if (!output.is_open()) {
		std::cout << "Error open file\n";
		exit(EXIT_FAILURE);
	}

  output << "digraph {\n";

  toGv(output);

  output << "}\n";

  output.close();
}

void NClassDec::toGv(std::ofstream& output, int idParent)
{
  outputBox(output, getIdNode());
  methods->toGv(output, getIdNode());
}

inline void NClassDec::outputBox(std::ofstream& output, int idNode)
{
  if (name != NULL) {
    output << "\t\"node" << idNode << "\""
          << "[shape=box, label=\"class"
          << "\\n" << name->getName() << "\"]\n";
  }
}

llvm::Value* NClassDec::codeGen(CodeGenContext& context)
{
  methods->codeGen(context);
}

NClassDec::~NClassDec()
{
  delete name;
  methods->free_ops();
  delete methods;
}