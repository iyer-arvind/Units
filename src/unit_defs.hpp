#ifndef UNITDEFS_H_INCLUDED
#define UNITDEFS_H_INCLUDED

#include <map>

#include "units.hpp"

namespace Units
{

typedef std::map<std::string, Unit> UnitDefMap; 
extern UnitDefMap unit_defs;

}
#endif
