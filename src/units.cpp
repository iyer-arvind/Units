#include "units.hpp"
#include "unit_defs.hpp"

namespace Units
{
Unit parse(std::string string);

Unit Unit::get_unit(std::string s, bool no_parse)
{
    if(! s.size())
        return Unit(); 
        
    auto const &x = unit_defs.find(s);
    if (x==unit_defs.end())
    {
        for(auto const &pu: unit_defs)
        if(pu.first[pu.first.size()-1] == '-')
        {
            std::string prefix = pu.first.substr(0, pu.first.size()-1);
            if(s.find(prefix) == 0)
            {
                std::string rem = s.substr(prefix.size());
                auto const &xx = unit_defs.find(rem);
                if (xx != unit_defs.end())
                { 
                    Unit ret = Unit(xx->second)*(pu.second);
                    ret._name = s;
                    return ret;
                }
            }
        }
        // PARSE THE STRING
        if(! no_parse)
        {
            return Units::parse(s);
        }
        throw std::logic_error(std::string("Unit :")+s+std::string(" not found. "));
    }
    else
    {
        return Unit(x->second);
    }
}

Quantity Quantity::to(const Unit &unit)const
{
    return Quantity(_value*double(_unit/unit), unit);
}

void Unit::to_stream(std::ostream& stream) const
{
    stream << _name;
}

Unit Unit::operator*(const Unit &u)const
{
    assert(is_zero_offset());
    return Unit(_name+std::string("*")+u.name(),
                _factor*u._factor,
                _dimension+u._dimension, 0); 
}

Unit& Unit::operator*=(const Unit &u)
{
    assert(is_zero_offset());
    _factor *= u._factor;
    _dimension += u._dimension;
    _name = _name + "*" + u._name;
    return *this;
}

Unit Unit::operator/(const Unit &u)const
{
    assert(is_zero_offset());
    return Unit(_name+std::string("/")+u.name(),
                _factor/u._factor,
                _dimension-u._dimension, 0); 
}

Unit& Unit::operator/=(const Unit &u)
{
    assert(is_zero_offset());
    _factor /= u._factor;
    _dimension -= u._dimension;
    _name = _name + "/" + u._name;
    return *this;
}



Unit Unit::operator^(double d)const
{
    assert(is_zero_offset());
    return Unit(_name+std::string("^")+std::to_string(d),
                std::pow(_factor, d),
                _dimension*d, 0); 
}

Unit& Unit::operator^=(double d)
{
    assert(is_zero_offset());
    _factor = std::pow(_factor, d);
    _dimension *= _dimension;
    _name = _name + "^" + std::to_string(d);
    return *this;
}


}
