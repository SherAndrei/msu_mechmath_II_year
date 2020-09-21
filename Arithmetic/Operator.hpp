#include <ostream>
#include <cmath>
#include <algorithm>
#define delta 10e-8


Number Sin(Number b)
{
    return Number((sin(b.val+b.eps)+sin(b.val-b.eps))/2,(sin(b.val+b.eps)-sin(b.val-b.eps))/2);
}

Number Cos(Number b)
{
    return Number((cos(b.val+b.eps)+cos(b.val-b.eps))/2,(cos(b.val+b.eps)-cos(b.val-b.eps))/2);
}


Number Integ (Number x1,Number x2,Number (*f)(Number))
{
    int i, N=100;
    Number s1,s2,s3,h,I1,I2,I,Delta(10e-8,10e-10);
    h = (x2 - x1)/(N);
    for (i=0; i<N; i++)
    {
        s1 = s1 + f(x1 + h*i) + f(x1 + h*(i+1));
        s2 = s2 + f(x1 + h*i + h/2);
    }
    I1 = (s1/6 + s2*2/3)*h;
    do
    {
        N = 2*N;
        h = h/2;
        for (i=0; i<N; i++)
        {
            s3 = s3 + f(x1 + h/2 + h*i);
        }
        s1 = (s1 + s2*2);
        s2 = s3;
        I2 = (s1/6 + (s2*2)/3)*h;
        I  = I2;
        I2 = I1;
        I1 = I;
    }
    while  ((I1-I2)>Delta || (I2-I1)>Delta);
//    cout << " h = " << h << endl;
    return I;
}

Number f(Number x)
{
    return (x);
}



