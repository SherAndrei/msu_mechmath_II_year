#include <ostream>
#define delta 10e-8

class Number {
    double val, eps;

 public:
    Number(double val, double eps);
    Number(const Number& r);
    Number();

    Number operator * (Number b);
    Number operator * (double k);
    Number operator * (int q);
    Number operator / (Number b);
    Number operator / (double k);
    Number operator / (int q);
    Number operator + (Number b);
    Number operator - (Number b);
    Number operator = (Number a);
    bool   operator != (Number b);
    bool   operator < (Number b);
    bool   operator > (Number b);
    bool   operator == (Number b);

    friend Number Sin(Number b);
    friend Number Cos(Number b);
    friend Number Integ(Number x1, Number x2, Number (*f)(Number));
    friend Number f(Number x);

    friend std::ostream& operator<<(std::ostream& out, const Number& a);
};
