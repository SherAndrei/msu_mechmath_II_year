#include <cmath>
#define PI 3.1415926535897932384626433832795
#include <fstream>

class line
{
    point a,v;

public:

    void SetP(double xx, double yy)
    {
        a.SetX(xx);
        a.SetY(yy);
        return;
    }
    void SetV(double xx, double yy)
    {
        v.SetX(xx);
        v.SetY(yy);
        return;
    }

    point GetA()const
    {
        return a;
    }

    point GetV()const
    {
        return v;
    }

    bool IsValid()
    {
        if (fabs(v.GetX())>0.00000001||fabs(v.GetY())>0.00000001)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Setline (point s,point t)
    {
        a=s;
        v.SetP(s.GetX()+(-1)*t.GetX(), s.GetY()+(-1)*t.GetY());
        return;
    }
    void Printline (FILE*f)
    {
        fprintf (f,"%lf ",a.GetX()-v.GetX());
        fprintf (f,"%lf\n",a.GetY()-v.GetY());
        fprintf (f,"%lf ",a.GetX()+v.GetX());
        fprintf (f,"%lf\n",a.GetY()+v.GetY());
    }
    friend point operator&(const line &a, const line &b);

};
