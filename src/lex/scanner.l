%option c++
%option     outfile="src/lex/scanner.cpp"
%option header-file="include/scanner.hxx"
%option 8bit warn nodefault
%option noyywrap

%{
  #include <stdexcept>
  #include <cstdlib>
  #include "../../include/parser.hxx"
  #include "../../include/scanner.h"

  #define YY_USER_ACTION          loc->step(); loc->columns(yyleng);
%}

identifer           [-]?[_a-zA-Z][a-zA-Z0-9_]*
string_literal      \"[^\n"]*\"
char                \'[^\n']\'
numeric_constant    [-]?[1-9][0-9]*|[0]
space               [ ]+
tab					        [\t]
new_line			      [\n]
single_line_comment [/]{2}.*

%%

%{
  loc->step();
%}

";"                         { return yy::parser::token::T_SEMI;     }
","                         { return yy::parser::token::T_COMMA;    }
"."                         { return yy::parser::token::T_POINT;    }
"{"                         { return yy::parser::token::T_L_BRACE;  }
"}"                         { return yy::parser::token::T_R_BRACE;  }
"["                         { return yy::parser::token::T_L_SQUARE; }
"]"                         { return yy::parser::token::T_R_SQUARE; }
"("                         { return yy::parser::token::T_L_PAREN;  }
")"                         { return yy::parser::token::T_R_PAREN;  }
"&&"                        { return yy::parser::token::T_AND;      }
"||"                        { return yy::parser::token::T_OR;       }
"+"                         { return yy::parser::token::T_ADD;      }
"-"                         { return yy::parser::token::T_SUB;      }
"*"                         { return yy::parser::token::T_MULT;     }
"/"                         { return yy::parser::token::T_DIV;      }
"%"                         { return yy::parser::token::T_MOD;      }
"="                         { return yy::parser::token::T_ASSIGN;   }
"<"                         { return yy::parser::token::T_LESS;     }
">"                         { return yy::parser::token::T_MORE;     }
"<="                        { return yy::parser::token::T_LESS_OR_EQUAL; }
">="                        { return yy::parser::token::T_MORE_OR_EQUAL; }
"=="                        { return yy::parser::token::T_EQUALLY;    }
"!="                        { return yy::parser::token::T_NOT_EQUAL;  }
"int"                       { return yy::parser::token::T_INT;        }
"char"                      { return yy::parser::token::T_CHAR;       }
"string"                    { return yy::parser::token::T_STRING;     }
"void"                      { return yy::parser::token::T_VOID;       }
"return"                    { return yy::parser::token::T_RETURN;     }
"if"                        { return yy::parser::token::T_IF;         }
"else"                      { return yy::parser::token::T_ELSE;       }
"while"                     { return yy::parser::token::T_WHILE;      }
"class"                     { return yy::parser::token::T_CLASS;      }
"static"                    { return yy::parser::token::T_STATIC;     }
"function"                  { return yy::parser::token::T_FUNCTION;   }
"new"                       { return yy::parser::token::T_NEW;        }
"outputStr"                 { return yy::parser::token::T_OUTPUTSTR;  }
"outputInt"                 { return yy::parser::token::T_OUTPUTINT;  }
"outputChar"                { return yy::parser::token::T_OUTPUTCHAR; }
"input"                     { return yy::parser::token::T_INPUT;      }
{string_literal}            {
                              val->strType = new std::string(yytext);
                              // std::cout << *val->strType << std::endl;
                              return yy::parser::token::T_STRING_LITERAL;
                            }
{char}                      {
                              val->ch = yytext[1];
                              // std::cout << val->ch << std::endl;
                              return yy::parser::token::T_ONE_CHAR;
                            }
{identifer}                 {
                              val->strType = new std::string(yytext);
                              // std::cout << *val->strType << std::endl;
                              return yy::parser::token::T_IDENTIFIER;
                            }
{numeric_constant}          {
                              val->intconst = std::atoi(yytext);
                              // val->strType = new std::string(yytext);
                              // std::cout << val->intconst << std::endl;
                              return yy::parser::token::T_NUMERIC_CONSTANT;
                            }
{single_line_comment}       { ; }
{space}                     { ; }
{tab}                       { loc->columns(); }
{new_line}					        { loc->lines(1); }
<<EOF>>						          { return yy::parser::token::T_END_OF_FILE; }
.                           { return yy::parser::token::T_UNKNOWN; }

%%

yy::scanner::scanner(std::istream* in, std::ostream* out) :
                     yyFlexLexer(in, out) { }

int yyFlexLexer::yylex()
{
  throw std::logic_error(
      "The yylex() exists for technical reasons and must not be used.");
}

