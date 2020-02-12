%output  "parser.cxx"
%defines "parser.hxx"

%skeleton "lalr1.cc"

%require "3.0.4"

%token-table

%parse-param  {yy::scanner* scanner}

%locations

%output  "src/parser/parser.cpp"
%defines "include/parser.hxx"

%define parse.error verbose

%debug

%define api.token.prefix {T_}

%code requires {
  #include <vector>
  #include "location.hh"

  #include "NStatement.h"
  #include "NExpression.h"
  #include "NClassDec.h"
  #include "NClassDec.h"
  #include "NFuncDec.h"
  #include "NBlock.h"
  #include "NIf.h"
  #include "NWhile.h"
  #include "NReturn.h"
  #include "NVarDec.h"
  #include "NMethodCall.h"
  #include "NExprStmt.h"
  #include "NAssignment.h"
  #include "NBinOper.h"
  #include "NInteger.h"
  #include "NElse.h"
  #include "NArrayDeclaration.h"
  #include "NChar.h"
  #include "NArrayElement.h"
  #include "NStmtExpr.h"
  #include "NOutputStr.h"
  #include "NOutputInt.h"
  #include "NOutputChar.h"

  namespace yy {
    class scanner;
  };

  int parse(const char*, NClassDec**, bool);
}

%code {

  #include "../../include/scanner.h"
  #include <string>
  #include <sstream>
  #include <fstream>
  #include <iostream>
  #include <vector>
  #include <algorithm>

  #include "../../include/NStatement.h"
  #include "../../include/NExpression.h"
  #include "../../include/NClassDec.h"
  #include "../../include/NClassDec.h"
  #include "../../include/NFuncDec.h"
  #include "../../include/NBlock.h"
  #include "../../include/NIf.h"
  #include "../../include/NWhile.h"
  #include "../../include/NReturn.h"
  #include "../../include/NVarDec.h"
  #include "../../include/NMethodCall.h"
  #include "../../include/NExprStmt.h"
  #include "../../include/NAssignment.h"
  #include "../../include/NBinOper.h"
  #include "../../include/NInteger.h"
  #include "../../include/NElse.h"
  #include "../../include/NArrayDeclaration.h"
  #include "../../include/NChar.h"
  #include "../../include/NArrayElement.h"
  #include "../../include/NStmtExpr.h"
  #include "../../include/NOutputStr.h"
  #include "../../include/NOutputInt.h"
  #include "../../include/NOutputChar.h"

  using std::move;

  #ifdef  yylex
  #undef yylex
  #endif
  #define yylex scanner->lex

  NClassDec *glob_root;

  int eRow;
  int eCol;

  NBinOper* createBinOper(std::string *op, NExpression *term,
                          NBinOper *binOper)
  {
    NBinOper *newBinOper = NULL;
    if (binOper) {
      binOper->setLhs(term);
      newBinOper = new NBinOper(*op, binOper);
    } else
      newBinOper = new NBinOper(*op, term);
    delete op;
    return newBinOper;
  }

  NExpression* createLhs(NExpression *expr, NBinOper *binOper)
  {
    NExpression *lhs = NULL;
    if (binOper) {
      binOper->setLhs(expr);
      lhs = binOper;
    } else
      lhs = expr;
    return lhs;
  }

  void setTypeInDeclaration(NIdentifier *type, NStatement *dec)
  {
    // declaration variable
    NVarDec *tmpVarDec = dynamic_cast<NVarDec*>(dec);
    if (tmpVarDec)
      tmpVarDec->setType(type);

    // declaration array
    NArrayDeclaration *tmpArrDec = dynamic_cast<NArrayDeclaration*>(dec);
    if (tmpArrDec)
      tmpArrDec->setType(type);

    // NStmtExpr * NStmtExpr(NStatement *stmt);

  }

  // vector concatenation (return new vecotr + old vector)
  VarList* createNewVecotor(NStatement *stmt, VarList *oldVarList)
  {
    VarList *varList = new VarList();
    varList->push_back(dynamic_cast<NVarDec*>(stmt));

    for (auto var : *oldVarList)
      varList->push_back(var);
    delete oldVarList;

    return varList;
  }

  ExpressionList* createNewVecotor(NExpression *expr,
                                   ExpressionList *oldExprList)
  {
    ExpressionList *exprList = new ExpressionList();
    exprList->push_back(expr);
  
    for (auto expr : *oldExprList)
      exprList->push_back(expr);
    delete oldExprList;

    return exprList;
  }

  NExprStmt* createExpressionStatement(NIdentifier *id, NExpression *expr)
  {
    NMethodCall *tmpMethodCal = dynamic_cast<NMethodCall*>(expr);
    if (tmpMethodCal) tmpMethodCal->setId(id);

    NAssignment *tmpAssignment = dynamic_cast<NAssignment*>(expr);
    if (tmpAssignment) {
      NArrayElement *tmpArrElem = dynamic_cast<NArrayElement*>(tmpAssignment->getLhs());
      if (tmpArrElem) {
        tmpArrElem->setName( id->getName() );
        delete id;
      } else
        tmpAssignment->setLhs(id);
    }

    return new NExprStmt(expr);
  }

  NExpression* defineExpression(NIdentifier *id, NExpression *expr)
  {
    NMethodCall *tmpMethodCal = dynamic_cast<NMethodCall*>(expr);
    if (tmpMethodCal) tmpMethodCal->setId(id);

    NArrayElement *tmpArrElem = dynamic_cast<NArrayElement*>(expr);
    if (tmpArrElem) {
      tmpArrElem->setName(id->getName());
      delete id;
    }
    
    return (expr) ? expr : id;
  }

  NExpression* addArrayToAssinment(NInteger *numConst, NExpression *expr)
  {
    NAssignment *tmpAssignment = dynamic_cast<NAssignment*>(expr);
    if (tmpAssignment)
      tmpAssignment->setLhs(new NArrayElement(numConst));
    
    return expr;
  }
}

%union
{
  char ch;
  int intconst;
  std::string *strType;

  NClassDec *nClassDec;
  NFuncDec *nFuncDec;
  NBlock *nBlock;
  NVarDec *nVarDec;
  NStatement *stmt;
  NExpression *expr;
  NIdentifier *ident;
  std::vector<NVarDec*> *varList;
  std::vector<NExpression*> *exprList;
  NMethodCall *nMethodCall;
  NBinOper *nBinOper;
  NElse *nElse;
  NArrayDeclaration *nArrDec;
  NInteger *nInt;
}

%start start
%token <strType>  L_BRACE R_BRACE L_SQUARE R_SQUARE L_PAREN R_PAREN
%token <strType>  SEMI COMMA POINT 
%token <strType>  ADD SUB MULT DIV MOD ASSIGN AND OR
%token <strType>  LESS LESS_OR_EQUAL MORE MORE_OR_EQUAL EQUALLY NOT_EQUAL
%token <strType>  INT CHAR STRING VOID
%token <strType>  RETURN IF ELSE WHILE CLASS STATIC NEW FUNCTION
%token <strType>  STRING_LITERAL
%token <ch>       ONE_CHAR
%token <strType>  IDENTIFIER
%token <intconst> NUMERIC_CONSTANT
%token            END_OF_FILE 0 "end of file"
%token            UNKNOWN
%token            OUTPUTSTR OUTPUTINT OUTPUTCHAR
%token            INPUT

%type <nClassDec>   class
%type <nFuncDec>    method
%type <nBlock>      method_list statement_list else_2

%type <stmt>        statement_init statement if while return arg
%type <stmt>        output outputStr outputInt outputChar
%type <stmt>        init init_var init_array

%type <ident>       ident return_type data_type

%type <expr>        def def_var def_array call_method method_or_array
%type <expr>        el_of_arr value_for_var sign_number char
%type <expr>        return_value init_value id_or_sign_number 
%type <nInt>        alloc num_const

%type <expr>        term group
%type <expr>        prior_11 prior_21 prior_31 prior_41
%type <nBinOper>    prior_12 prior_22 prior_32 prior_42
%type <strType>     prior_oper1 prior_oper2 prior_oper3 prior_oper4
%type <strType>     condition

%type <varList>     arg_list tail_arg_list
%type <exprList>    pass_arg tail_pas_arg

%type <nElse>       else_1

%%

start:  class {}
     ;

class:  method_list { glob_root = new NClassDec($1); }
     ;

method_list:  method method_list  { $$ = new NBlock($1, $2); }
           |  %empty              { $$ = new NBlock(); }
           ;

method: FUNCTION return_type ident L_PAREN arg_list R_PAREN
        L_BRACE
          statement_list
        R_BRACE { $$ = new NFuncDec($2, $3, $5, $8); }
      ;

return_type:  data_type { $$ = $1; }
           |  VOID      { $$ = new NIdentifier(std::string("void")); }
           ;

statement_list: statement_init statement_list { $$ = new NBlock($1, $2); }
              | statement statement_list      { $$ = new NBlock($1, $2); }
              | %empty                        { $$ = new NBlock(); }
              ;

statement_init: data_type init  { setTypeInDeclaration($1, $2); $$ = $2; }
              ;

init: init_var      { $$ = $1; }
    | init_array    { $$ = $1; }
    ;

init_var: ident init_value SEMI  { $$ = new NVarDec($1, $2); }
        ;

init_value: def_var { $$ = $1; }
          | %empty  { $$ = NULL; };
          ;

init_array: ident alloc SEMI { $$ = new NArrayDeclaration($1, $2); }
          ;

alloc: ASSIGN NEW data_type L_PAREN num_const R_PAREN { $$ = $5; delete $3; }
     | %empty                                           { $$ = NULL; }
     ;

statement: ident def SEMI { $$ = createExpressionStatement($1, $2); }
         | if             { $$ = $1; }
         | while          { $$ = $1; }
         | return         { $$ = $1; }
         | output         { $$ = $1; }
         ;

output: outputStr   { $$ = $1; }
      | outputInt   { $$ = $1; }
      | outputChar  { $$ = $1; }
      ;

outputStr: OUTPUTSTR L_PAREN STRING_LITERAL R_PAREN SEMI  { $$ = new NOutputStr(*$3); delete $3; }
         ;

outputInt: OUTPUTINT L_PAREN term R_PAREN SEMI { $$ = new NOutputInt($3); }
         ;

outputChar: OUTPUTCHAR L_PAREN term R_PAREN SEMI { $$ = new NOutputChar($3); }
          ;

def: def_var       { $$ = $1; }
   | def_array     { $$ = $1; }
   | call_method   { $$ = $1; }
   ;

def_var: ASSIGN value_for_var { $$ = new NAssignment($2); }
       ;

value_for_var: term      { $$ = $1; }
             | char      { $$ = $1; }
             ;

char: ONE_CHAR { $$ = new NChar($1); }
    ;

id_or_sign_number: ident method_or_array  { $$ = defineExpression($1, $2); }
                 | sign_number            { $$ = $1; }
                 ;

method_or_array: call_method  { $$ = $1; }
               | el_of_arr    { $$ = $1; }
               | %empty       { $$ = NULL; }
               ;

el_of_arr: L_SQUARE num_const R_SQUARE  { $$ = new NArrayElement($2); }
         ;

call_method: L_PAREN pass_arg R_PAREN  { $$ = new NMethodCall($2); }
           ;

pass_arg: term tail_pas_arg { $$ = createNewVecotor($1, $2); }
        | %empty            { $$ = new ExpressionList(); }
        ;

tail_pas_arg: COMMA term tail_pas_arg { $$ = createNewVecotor($2, $3); }
            | %empty                  { $$ = new ExpressionList(); }
            ;

term: prior_11 { $$ = $1; }
    ;

prior_11: prior_21 prior_12 { $$ = createLhs($1, $2); }
        ; 
prior_12: prior_oper1 prior_21 prior_12 { $$ = createBinOper($1, $2, $3); }
        | %empty                        { $$ = NULL; }
        ;

prior_21: prior_31 prior_22 { $$ = createLhs($1, $2); }
        ;
prior_22: prior_oper2 prior_31 prior_22 { $$ = createBinOper($1, $2, $3); }
        | %empty                        { $$ = NULL; }
        ;

prior_31: prior_41 prior_32 { $$ = createLhs($1, $2); }
        ;
prior_32: prior_oper3 prior_41 prior_32 { $$ = createBinOper($1, $2, $3); }
        | %empty                        { $$ = NULL; }
        ;

prior_41: group prior_42 { $$ = createLhs($1, $2); }
        ;
prior_42: prior_oper4 group prior_42  { $$ = createBinOper($1, $2, $3); }
        | %empty                      { $$ = NULL; }
        ;

group: L_PAREN term R_PAREN { $$ = $2; }
     | id_or_sign_number    { $$ = $1; }
     ;

prior_oper4: MULT { $$ = new std::string("*"); }
           | DIV  { $$ = new std::string("/"); }
           ;

prior_oper3: ADD { $$ = new std::string("+"); }
           | SUB { $$ = new std::string("-"); }
           ;

prior_oper2: condition { $$ = $1; }
           ;

prior_oper1: AND  { $$ = new std::string("&&"); }
           | OR   { $$ = new std::string("||"); }
           ;

def_array: L_SQUARE num_const R_SQUARE def_var  { $$ = addArrayToAssinment($2, $4); }
         ;

if: IF L_PAREN term R_PAREN L_BRACE
      statement_list
    R_BRACE else_1  { $$ = new NIf($3, $6, $8); }
  ;

else_1: ELSE else_2 { $$ = new NElse($2); }
      | %empty      { $$ = NULL; }
      ;

else_2: L_BRACE statement_list R_BRACE  { $$ = $2; }
      | if                              { $$ = new NBlock($1); }
      ;

while:  WHILE L_PAREN term R_PAREN L_BRACE
          statement_list
        R_BRACE { $$ = new NWhile($3, $6); }
     ;

return: RETURN return_value SEMI  { $$ = new NReturn($2); }
      ;

return_value: value_for_var { $$ = $1; }
            | %empty        { $$ = NULL; }
            ;

condition:  EQUALLY       { $$ = new std::string("=="); }
         |  NOT_EQUAL     { $$ = new std::string("!="); }
         |  LESS          { $$ = new std::string("<");  }
         |  LESS_OR_EQUAL { $$ = new std::string("<="); }
         |  MORE          { $$ = new std::string(">");  }
         |  MORE_OR_EQUAL { $$ = new std::string(">="); }
         ;

data_type:  INT  { $$ = new NIdentifier(std::string("int")); }
         |  CHAR { $$ = new NIdentifier(std::string("char")); }
         ;

arg_list: arg tail_arg_list { $$ = createNewVecotor($1, $2); }
        | %empty            { $$ = new VarList(); }
        ;

tail_arg_list:  COMMA arg tail_arg_list { $$ = createNewVecotor($2, $3); }
             |  %empty                  { $$ = new VarList(); }
             ;

arg:  data_type ident  { $$ = new NVarDec($1, $2); }
   ;

sign_number:  sign num_const { $$ = $2; }
           ;

sign: SUB    { ; }
    | ADD    { ; }
    | %empty { ; }
    ;

ident:  IDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
     ;

num_const: NUMERIC_CONSTANT { $$ = new NInteger($1); }
         ;

%%

void yy::parser::error(const parser::location_type& l, const std::string& m)
{
  throw yy::parser::syntax_error(l, m);
}

int parse(const char* file, NClassDec **root, bool out_error)
{
  std::ifstream *yyin;
  yyin = new std::ifstream(file);
  
  yy::scanner scanner(yyin);
  yy::parser parser(&scanner);
  try {
    int result = parser.parse();
    if (result != 0) 
      throw std::runtime_error("Unknown parsing error");
    *root = glob_root;
  } catch (yy::parser::syntax_error& e) {
    eCol = e.location.begin.column;
    // int len = 1 + e.location.end.column - col;
    eRow = e.location.begin.line;

    std::ostringstream msg;
    msg << e.what() << "\n"
        << "in row " << eRow
        << " col " << eCol;
    
    if (out_error)
      std::cout << msg.str() << std::endl;
    // throw yy::parser::syntax_error(e.location, msg.str());

    yyin->close();
    return 1;
  }
  
  yyin->close();
  return 0;
}