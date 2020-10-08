#include "Number.h"
#include <ostream>
#include <cmath>

#define delta 10e-8

Number::Number(double val, double eps)
{
	this->val = val;
	this->eps = eps;
}

Number::Number(const Number& r)
{
	this->val = r.val;
	this->eps = r.eps;
}

Number::Number()
{
	this->val = 0;
	this->eps = 0;
}

Number Number::operator * (Number b)
{
	return Number((this->val) * (b.val), fabs((this->val) * fabs(b.eps) + (b.val) * fabs(this->eps)));
}

Number Number::operator * (double k)
{
	if (fabs(k)<delta)
		return Number(0,0);

	return Number((this->val) * k, fabs(this->eps));
}

Number Number::operator * (int q)
{
	if (q == 0)
		return Number(0,0);

	return Number((this->val) * q, fabs(this->eps));
}

Number Number::operator / (Number b)
{
	if ((fabs(b.val))<delta) return *this;
	return Number((fabs(this->val) + fabs(this->eps)) / (fabs(b.val) + fabs(b.eps)), fabs(fabs(this->eps)/fabs(b.val) - (fabs(this->val) * fabs(b.eps))/(fabs(b.val) * fabs(b.val))));
}

Number Number::operator / (double k)
{
	if (fabs(k)<delta)
		return Number(0,0);

	return Number((this->val) / k, fabs(this->eps));
}

Number Number::operator / (int q)
{
	if (q == 0)
		return Number(0,0);

	return Number((this->val) / q, fabs(this->eps));
}

Number Number::operator + (Number b)
{
	return Number((this->val)+(b.val), fabs(this->eps) + fabs(b.eps));
}

Number Number::operator - (Number b)
{
	return Number((this->val) - (b.val), fabs(this->eps) + fabs(b.eps));
}
Number Number::operator = (Number a)
{
	if (*this != a)
		{
		this->val = a.val;
		this->eps = a.eps;
		}
	return *this;
}

bool   Number::operator != (Number b)
{
	return !(*this==b);
}
//    bool operator <= (Number b);
//    bool operator >= (Number b);
bool   Number::operator < (Number b)
{
	return (*this - b).val < 0;
}
bool   Number::operator > (Number b)
{
	return (*this - b).val > 0;
}
bool   Number::operator == (Number b)
{
	return ((fabs(this->val - b.val))<delta && (fabs(this->eps - b.eps))<delta);
}

std::ostream& operator<<(std::ostream& out, const Number& a)
{
	out << a.val << " +- " << a.eps << std::endl;
	return out;
}
