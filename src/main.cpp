#include "../include/scanner.h"
#include <string>
#include <cstring>
#include <fstream>
#include <iostream>

#include "../include/NClassDec.h"

#include "../include/CodeGenContext.h"

#include <llvm-6.0/llvm/Support/raw_ostream.h>
#include <llvm-6.0/llvm/Support/FileSystem.h>
#include <llvm-6.0/llvm/Bitcode/BitcodeWriter.h>

using namespace llvm;

#define START_TOKEN 258

#include <llvm-6.0/llvm/Support/raw_ostream.h>
#include <llvm-6.0/llvm/Support/FileSystem.h>
#include <llvm-6.0/llvm/Bitcode/BitcodeWriter.h>

const char *token_names[] =
{
	"SEMI",
	"COMMA",
	"POINT",
	"L_BRACE",
	"R_BRACE",
	"L_SQUARE",
	"R_SQUARE",
	"L_PAREN",
	"R_PAREN",
	"ADD",
	"SUB",
	"MULT",
	"DIV",
	"MOD",
	"ASSIGN",
	"LESS",
	"LESS_OR_EQUAL",
	"MORE",
	"MORE_OR_EQUAL",
	"EQUALLY",
	"NOT_EQUAL",
	"INT",
	"CHAR",
	"STRING",
	"VOID",
	"RETURN",
	"IF",
	"ELSE",
	"WHILE",
	"CLASS",
	"STATIC",
	"NEW",
	"STRING_LITERAL",
	"ONE_CHAR",
	"IDENTIFIER",
	"NUMERIC_CONSTANT",
	"END_OF_FILE",
	"UNKNOWN",
	NULL
};

int test(int x)
{
	std::cout << x << std::endl; 
}

extern int eRow;
extern int eCol;

int main(int argc, char** argv) 
{
	if (argv[1] != NULL && std::string(argv[1]) == "--s") {
		std::ifstream *yyin;
		std::string filename; 

		#if 0
		if (argc == 2) {
			yyin = new std::ifstream(argv[1]);
			filename = std::string(argv[1]);
		} else if (argc == 3) {
			yyin = new std::ifstream(argv[2]);
			filename = std::string(argv[2]);
		}
		#else
		yyin = new std::ifstream(argv[2]);
		filename = std::string(argv[2]);
		#endif
		
		if (!yyin->is_open()) {
			std::cerr << "I can not open file." << std::endl;
			exit(EXIT_FAILURE);
		}
		
		yy::parser::symbol_type yyla;
		yy::scanner scanner(yyin);

		yyla.location.initialize(&filename);

		int token_type;

		do {
			token_type = scanner.lex(&yyla.value, &yyla.location);

			int col = yyla.location.begin.column;
			int row = yyla.location.begin.line;

			std::cout << "Loc=<" << *(yyla.location.begin.filename);
			std::cout << ":" << row;
			std::cout << ":" << col << ">\t";
			
			if (token_type != yy::parser::token::T_END_OF_FILE)
				std::cout << token_names[token_type - START_TOKEN] << " ";
			else
				std::cout << "END_OF_FILE" << " ";
			
			std::cout << "'" << scanner.YYText() << "'" << std::endl;

			// std::cout << "yyval" << yyla.value. << std::endl;
			// yy::parser::symbol_number_type
			// yy::

		} while(token_type != yy::parser::token::T_END_OF_FILE);
	
		yyin->close();
	} else {
		NClassDec *root;
		if (!parse("data/Program.cs", &root, true))
			root->createGraph();

		#if 1
		std::error_code ErrorInfo;

  	raw_fd_ostream OS("./data/code_gen.bc", ErrorInfo, sys::fs::F_None);

		if (ErrorInfo) {
			errs() << "Could not open file: " << ErrorInfo.message();
			return -1;
		}
		CodeGenContext context;
		root->codeGen(context);

		context.getModule()->print(errs(), nullptr);
		// segm fault gen for else
		WriteBitcodeToFile(context.getModule(), OS);
		#endif

		delete root;
	}

	return 0;
}
