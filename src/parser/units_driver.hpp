#ifndef __UnitsDRIVER_HPP__
#define __UnitsDRIVER_HPP__ 1

#include <string>
#include <cstddef>
#include <istream>

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "units_parser.tab.hh"
#include "location.hh"
#include "units.hpp"

namespace Units
{
class Units_Scanner : public yyFlexLexer
{
private:
    Units::Units_Parser::semantic_type *yylval = nullptr;
    Unit _value;
   
public:   
   Units_Scanner(std::istream *in) : yyFlexLexer(in)
   {}
   
   void set_value(const Unit &val) {_value = val;}
   
   const Unit& value()const {return _value; }
   
   virtual int yylex( Units::Units_Parser::semantic_type * const lval, 
                      Units::Units_Parser::location_type *location );
   

};

Unit parse(std::string string);

} 
#endif 
