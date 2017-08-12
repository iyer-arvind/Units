%{
/* C++ string header, for string ops below */
#include <string>

/* Implementation of yyFlexScanner */ 
#include "units_driver.hpp"

#undef  YY_DECL
#define YY_DECL int Units::Units_Scanner::yylex( Units::Units_Parser::semantic_type * const lval,\
                                                 Units::Units_Parser::location_type *loc )

/* typedef to make the returns for the tokens shorter */
using token = Units::Units_Parser::token;

%}

%option debug
%option nodefault
%option yyclass="Units::Units_Scanner"
%option noyywrap
%option c++

%%
%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

[a-zA-Z]+   {
		       yylval->build<std::string>( yytext );
               return token::DIMS;
            }
[0-9]*\.*[0-9]* {  
                yylval->build<double>(atof(yytext));
                return token::NUMBER;
            }
\/	        {  return token::DIV;}
\*	        {  return token::MUL;}
\^	        {  return token::POW;}
\(          {  return token::PO;}
\)          {  return token::PC;}
.	        
\n          
%%
