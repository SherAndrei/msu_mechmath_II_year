#define PI 3.1415926535897932384626433832795
#include <fstream>
class segment
{
    point a,b;
    int z;
public:

    void Setseg(point aa,point bb)
    {
        a=aa;
        b=bb;
        return;
    }

    segment ()
    {
        a.SetP(0,0);
        b.SetP(1,0);
        z=1;
    }
    point GetA()
    {
        return a;
    }
    point GetB()
    {
        return b;
    }
    void SetS (point aa,point bb, int zz)
    {
        a=aa;
        b=bb;
        z=zz;
        return;
    }

    void SetZ(int x)
    {
        z=x;
        return;
    }
    int GetZ()
    {
        return z;
    }

    double Length ()
    {
        double h;
        h = sqrt ((a.GetX()-b.GetX())*(a.GetX()-b.GetX())+(a.GetY()-b.GetY())*(a.GetY()-b.GetY()));
        return h;
    }

    void Printsegment(FILE*f)
    {
        fprintf(f, "%lf ",a.GetX());
        fprintf(f, "%lf\n",a.GetY());
        fprintf(f, "%lf ",b.GetX());
        fprintf(f, "%lf\n",b.GetY());
        fprintf(f,"         \n");
    }

};
