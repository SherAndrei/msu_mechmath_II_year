#define PI 3.1415926535897932384626433832795
#include <fstream>

class circle
{
    point a;
    double r;

public:
    void SetC (point aa, double rr)
    {
        a.SetP(aa.GetX(),aa.GetY());
        r=rr;
        return;
    }

    point GetA()const
    {
        return a;
    }
    double GetR()const
    {
        return r;
    }

    bool IsValid ()
    {
        if (r>0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    friend segment operator&(const circle &a, const circle &b);

    void Printcircle(FILE*f)
    {
        double yy;
        point s;
        int i;
        s.setpoint(r,0,1);
        yy=2*PI/1000;
        for(i=1;i<1001;i++)
        {
            s.setpoint (a.GetX()+r*cos(yy*i),a.GetY()+r*sin(yy*i),1 );
            fprintf(f,"%lf ",s.GetX());
            fprintf(f,"%lf\n",s.GetY());
        }
        fprintf(f,"         \n");
        return;
    }

};
