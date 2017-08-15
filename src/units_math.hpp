#include <cmath>
#define WRAP_CMATH(X) \
inline \
double X(const Quantity& Q)\
{return std::X((double) Q);}

namespace Units
{
WRAP_CMATH(cos)
WRAP_CMATH(sin)
WRAP_CMATH(tan)
WRAP_CMATH(acos)
WRAP_CMATH(asin)
WRAP_CMATH(atan)
WRAP_CMATH(cosh)
WRAP_CMATH(sinh)
WRAP_CMATH(tanh)
WRAP_CMATH(acosh)
WRAP_CMATH(asinh)
WRAP_CMATH(atanh)
WRAP_CMATH(exp)
WRAP_CMATH(log)
WRAP_CMATH(log10)
WRAP_CMATH(exp2)
WRAP_CMATH(expm1)
WRAP_CMATH(log1p)
WRAP_CMATH(log2)
WRAP_CMATH(logb)
WRAP_CMATH(sqrt)
WRAP_CMATH(cbrt)
WRAP_CMATH(erf)
WRAP_CMATH(erfc)

Quantity pow(const Quantity &x, double p)
{
	return Quantity(std::pow(x.value(), p), x.unit()^p);
}
Quantity hypot(const Quantity &x, const Quantity &y)
{
	assert(x.unit().similar(y.unit()));
	return Quantity(std::hypot(x.value(), y.to(x.unit()).value()), x.unit());
}

double atan2(const Quantity &y, const Quantity &x)
{
	assert(y.unit().similar(x.unit()));
	return std::hypot(y.value(), x.to(y.unit()).value());
}

}
