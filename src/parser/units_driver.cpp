#include <cctype>
#include <sstream>
#include <cassert>

#include "units_driver.hpp"
#include "units.hpp"

namespace Units
{


Unit parse(std::string str)
{
   std::istringstream sstream(str);
   
   Units_Scanner scanner(&sstream );
   Units_Parser parser(scanner);

   parser.parse();
   return scanner.value();
}

}
