#ifndef LEXER_H
#define LEXER_H

# undef yyFlexLexer
# include <FlexLexer.h>
# include "parser.hxx"

# undef YY_DECL
# define YY_DECL  int yy::scanner::lex(                \
                      yy::parser::semantic_type* val,  \
                      yy::parser::location_type* loc)

namespace yy
{

  class scanner : public yyFlexLexer
  {
  public:
    explicit scanner(std::istream* in=0, std::ostream* out=0);

    int lex(parser::semantic_type* val, parser::location_type* loc);
  };
}

#endif