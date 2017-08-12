%skeleton "lalr1.cc"
%require  "3.0"
%debug 
%defines 
%define api.namespace {Units}
%define parser_class_name {Units_Parser}

%code requires{
#include "units.hpp"
   namespace Units 
   {
      class Units_Scanner;
   }

# ifndef YY_NULLPTR
#   define YY_NULLPTR nullptr
# endif
}

%parse-param { Units_Scanner  &scanner  }

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   
   /* include for all driver functions */
   #include "units_driver.hpp"

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%token <std::string> DIMS
%token <double> NUMBER
%token PO PC DIV MUL POW
%token END 0 

%type <Units::Unit> exprs
%type <Units::Unit> end
%type <Units::Unit> unit
%type <Units::Unit> exponent



%locations

%%

end     : exprs END            {scanner.set_value($1);}

exprs   : exponent             {$$=$1;}
        | exprs DIV exponent   {$$=$1/$3;}
        | exprs MUL exponent   {$$=$1*$3;}
        ;

exponent: unit              {$$=$1;}
        | unit POW NUMBER   {$$=$1^$3;}
        ;

unit    : DIMS              {$$=Units::Unit::get_unit($1, true);}
        | PO exprs PC       {$$=$2;}
        ;

%%


void 
Units::Units_Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
   throw std::invalid_argument(err_message);
}
