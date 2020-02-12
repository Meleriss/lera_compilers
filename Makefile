BIN_NAME := main

LLVM_CONFIG ?= /usr/bin/llvm-config

SRC_PATH	:= src
LEX_PATH	:= $(SRC_PATH)/lex
PARS_PATH := $(SRC_PATH)/parser
AST_PATH	:= $(SRC_PATH)/ast

BUILD_PATH	:= build
BIN_PATH 		:= bin

SRC_EXT := cpp

LLVMLIBS = $(shell $(LLVM_CONFIG) --libs bitreader support)

COMPILE_FLAGS := -g -Isrc/parser -Iinclude $(LLVMLIBS) -I/usr/include/llvm-c-6.0/ -I/usr/include/llvm-6.0/

SRC_FILES := $(SRC_PATH) $(PARS_PATH) $(LEX_PATH) $(AST_PATH)
SRC_FILES := $(wildcard $(addsuffix /*.$(SRC_EXT), $(SRC_FILES)))
OBJECTS := $(addprefix $(BUILD_PATH)/, $(notdir $(SRC_FILES:.$(SRC_EXT)=.o)))

.PHONY: dirs clean lex pars test run full

all: dirs $(BIN_PATH)/$(BIN_NAME)

full: dirs pars lex $(BIN_PATH)/$(BIN_NAME)

$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	g++ -std=c++17 $^ -o $@ $(COMPILE_FLAGS)

VPATH := $(SRC_PATH) $(PARS_PATH) $(LEX_PATH) $(AST_PATH)
$(BUILD_PATH)/%.o: %.cpp
	g++ -std=c++17 $< -c -o $@ $(COMPILE_FLAGS)

lex: src/lex/scanner.l
	flex src/lex/scanner.l

pars: src/parser/parser.yy
	bison -d -v -t -k  src/parser/parser.yy

SRC_FILES_TEST := $(PARS_PATH) $(LEX_PATH) $(AST_PATH)
SRC_FILES_TEST := $(wildcard $(addsuffix /*.$(SRC_EXT), $(SRC_FILES_TEST)))
OBJECTS_TEST := $(addprefix $(BUILD_PATH)/, $(notdir $(SRC_FILES_TEST:.$(SRC_EXT)=.o)))

test: dirs pars lex $(BIN_PATH)/test_parser
	./$(BIN_PATH)/test_parser

$(BIN_PATH)/test_parser: $(SRC_PATH)/test/runner_test_parser.cpp $(SRC_PATH)/test/test_parser.cpp $(OBJECTS_TEST)
	g++ -std=c++17 $^ -o $@ $(COMPILE_FLAGS)

$(BUILD_PATH)/%.o: $(SRC_PATH)/test/%.cpp
	g++ -std=c++17 $< -c -o $@ $(COMPILE_FLAGS)

$(SRC_PATH)/test/runner_test_parser.cpp: $(SRC_PATH)/test/test_parser.h
	cxxtestgen --runner=ErrorPrinter -o $@ $<

dirs:
	@mkdir $(BUILD_PATH) -p
	@mkdir $(BIN_PATH) -p

clean:
	@rm -rf $(BIN_PATH)
	@rm -rf $(BUILD_PATH)

run:
	./bin/main
	llvm-dis data/code_gen.bc

bctoll:
	llvm-dis data/code_gen.bc -o data/code_gen.ll

compile:
	make run
	llc -filetype=obj data/code_gen.bc -o data/code_gen.o
	clang data/helper_output.c -c -o data/helper_output.o
	clang data/code_gen.o data/helper_output.o -o data/code_gen
	./data/code_gen