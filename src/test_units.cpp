#include "units.hpp"

#include <iostream>

int main()
{
    Units::Quantity u1(5.0, "cm");
    Units::Quantity u2(2.0, "inch");
    Units::Quantity u3(2.0, "acre");
    
    
    std::cout <<"u1: "<< u1 <<"\nu2: "<< u2 <<"\nu1+u2: "<< (u1+u2) <<"\nu2+u1: "<<(u2+u1)  <<"\nu1/u2: "<< u1/u2<<"\n"<<"u1*u1+u3: "<<(u1*u1+u3)<<"\n";
    
    std::cout<<u3.to(Units::Unit("hectare"))<<std::endl;

    Units::Quantity u4(1, "cm");
    std::cout<<(u2.unit() == u4.unit())<<std::endl;
    return 0;
}
