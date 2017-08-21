#ifndef UNITS_HPP_INCLUDED
#define UNITS_HPP_INCLUDED

#include <string>
#include <ostream>
#include <iostream> 
#include <sstream>
#include <cmath>
#include <valarray>
#include <assert.h>

#define SMALL 1e-8

namespace Units
{
class Unit
{
private:
    std::string _name;
    double _factor;
    std::valarray<double> _dimension;
    double _offset;
    
public:
    Unit():
        _name(""),
        _factor(1),
        _dimension({0, 0, 0, 0, 0, 0, 0}),
        _offset(0)
    {}
    
    Unit(std::string name,
         double factor,
         std::valarray<double> dims, 
         double offset):
            _name(name),
            _factor(factor),
            _dimension(dims),
            _offset(offset)
    {}
    
    static
    Unit get_unit(std::string name, bool no_parse=false);
    
    
    Unit(std::string name):
        Unit(get_unit(name))
    {}
    
    void to_stream(std::ostream &stream)const;
    
    Unit operator*(const Unit &u)const;
    Unit operator/(const Unit &u)const;
    Unit operator^(double d)const;
    
    Unit &operator *=(const Unit&unit);
    Unit &operator /=(const Unit&unit);
    Unit &operator ^=(double d);
    
    operator double() const
    {
        assert(is_dimensionless());
        assert(is_zero_offset());
        return _factor;
    }

    bool operator==(const Unit& unit)const;
    bool similar(const Unit& unit)const;
    
    double factor()const {return _factor;}
    double offset()const {return _offset;}
    
    std::string dimstr() const
    {
        std::stringstream s;
        s<<"[";
        for(auto const &x:_dimension)
        {
            s<<x<<" ";
        }
        s<<"]";
        return s.str();
        
    }
    
    bool is_dimensionless() const
    {
        for(int i=0;i<7;i++) if(std::fabs(_dimension[i])>SMALL) return false;
        return true;
    }
    
    bool is_zero_offset() const
    {
        return fabs(_offset) < SMALL;
    }
    
    std::string name() const {return _name;}
    
    std::string to_string()const
    {std::stringstream ss;to_stream(ss);return ss.str();}
};

inline
std::ostream & operator<<(std::ostream& stream, const Unit &u)
{u.to_stream(stream); return stream;}

class Quantity
{
private:
    double _value;
    Unit _unit;
    
public:
    Quantity(double value, const Unit& unit):
        _value(value),
        _unit(unit)
    {}
    
    Quantity(const Quantity& other):
        _value(other._value),
        _unit(other._unit)
    {}
    
    Quantity(const Unit& unit):
        _value(1),
        _unit(unit)
    {}
    
    //explicit
    Quantity(double value=0, std::string unit=""):
        _value(value),
        _unit(Unit::get_unit(unit))
    {}
    
    void set_unit(const Unit& unit)
    {_unit = unit;}
    
    void set_value(double value)
    {_value = value;}
    
    Quantity to(const Unit& unit) const;
    
    void to_stream(std::ostream &stream)const
    {stream<<_value<<" "<<_unit.name();}
    
    std::string to_str() const
    {std::stringstream ss;to_stream(ss);return ss.str();}
    
    Quantity operator*(const Quantity& q) const
    {return Quantity(_value*q._value, _unit*q._unit);}
    
    Quantity operator/(const Quantity& q) const
    {return Quantity(_value/q._value, _unit/q._unit);}
    
    Quantity operator+(const Quantity& q) const
    {return Quantity(_value+q._value*(q._unit/_unit), _unit);}
    
    Quantity operator-(const Quantity& q) const
    {return Quantity(_value-q._value*(q._unit/_unit), _unit);}
    
    std::string to_string() const
    {std::stringstream ss;to_stream(ss);return ss.str();}
    
    explicit
    operator double() const
    {
        assert(_unit.is_dimensionless());
        return _value*_unit.factor();
    }
    
    const Unit& unit() const {return _unit;}

    const double& value() const {return _value;}
};

inline
Quantity operator*(double d, const Quantity &q)
{return Quantity(d*q.value(),q.unit());}

inline
Quantity operator/(double d, const Quantity &q)
{return Quantity(d)/q;}

inline
Quantity operator+(double d, const Quantity &q)
{return Quantity(d)+q;}

inline
Quantity operator-(double d, const Quantity &q)
{return Quantity(d)-q;}

inline
std::ostream & operator<<(std::ostream& stream, const Quantity &q)
{q.to_stream(stream); return stream;}

    
}
#endif
