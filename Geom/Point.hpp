#define PI 3.1415926535897932384626433832795
#include <fstream>

class point
{
    double x,y;
    bool z;
public:

    void SetX (double xx)
    {
        x=xx;
        return;
    }
    void SetY (double yy)
    {
        y=yy;
        return;
    }

    void SetZ (bool e)
    {
        z=e;
        return;
    }
    void setpoint (double xx,double yy, bool zz)
    {
        x=xx;
        y=yy;
        z=zz;
    }

    bool GetZ()const
    {
        return z;
    }

    void SetP(double xx, double yy)
    {
        x=xx;
        y=yy;
        return;
    }
    double GetX ()const
    {
        return x;
    }
    double GetY ()const
    {
        return y;
    }

    point ()
    {
        x=0;
        y=0;
        z=true;
    }

    point operator+(const point&)const;

    friend point operator*(const point &a, double z);

    void Printpoint (FILE*f)
    {
        fprintf(f, "plot [-0.01:0.01] %f+t,%f+t\n",x,y);
    }

};
