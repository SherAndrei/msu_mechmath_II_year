#include <cmath>
#include "Point.h"
#include "Line.h"
#include "Segment.h"
#include "Circle.h"

#define PI 3.1415926535897932384626433832795

Point Point::operator+(const Point & b)const
    {
        Point s;
        s.SetX(x+b.x);
        s.SetY(y+b.y);
        return s;
    }

Point  operator*(const Point &a,double z)
    {
        Point aa;
        aa.SetX(a.x*z);
        aa.SetY(a.y*z);
        return aa;
    }


Point operator&(const Line &a,const Line &b)
{

    Point aa,bb,cc;
    double u,c;
    if (fabs(a.v.GetX()*b.v.GetY()-a.v.GetY()*b.v.GetX())<0.00000000001)
    {

        aa= a.v;
        aa.SetZ(false);
        return aa;
    }
    else
    {

        aa=a.a+a.v;
        bb=b.a+b.v;
        u=((a.a.GetX()*aa.GetY()-aa.GetX()*a.a.GetY())*(b.a.GetX()-bb.GetX())-(b.a.GetX()*bb.GetY()-b.a.GetY()*bb.GetX())*(a.a.GetX()-aa.GetX()))/((a.a.GetX()-aa.GetX())*(b.a.GetY()-bb.GetY())-(b.a.GetX()-bb.GetX())*(a.a.GetY()-aa.GetY()));
        c=((a.a.GetX()*aa.GetY()-aa.GetX()*a.a.GetY())*(b.a.GetY()-bb.GetY())-(b.a.GetX()*bb.GetY()-b.a.GetY()*bb.GetX())*(a.a.GetY()-aa.GetY()))/((a.a.GetX()-aa.GetX())*(b.a.GetY()-bb.GetY())-(b.a.GetX()-bb.GetX())*(a.a.GetY()-aa.GetY()));
        cc.SetX(u);
        cc.SetY(c);
        return cc;
    }
}


Segment operator&(const Circle &c, const Line &a )
{
    Segment n;
    double D,k1,k2;
    D=4*(a.GetA().GetX()*a.GetV().GetX()+a.GetA().GetY()*a.GetV().GetY()-a.GetV().GetY()*c.GetA().GetY()-a.GetV().GetX()*c.GetA().GetX())*(a.GetA().GetX()*a.GetV().GetX()+a.GetA().GetY()*a.GetV().GetY()-a.GetV().GetY()*c.GetA().GetY()-a.GetV().GetX()*c.GetA().GetX());
    D=D-4*(a.GetV().GetX()*a.GetV().GetX()+a.GetV().GetY()*a.GetV().GetY())  *  (a.GetA().GetX()*a.GetA().GetX()+a.GetA().GetY()*a.GetA().GetY()+c.GetA().GetX()*c.GetA().GetX()+c.GetA().GetY()*c.GetA().GetY()-2*a.GetA().GetX()*c.GetA().GetX()-2*a.GetA().GetY()*c.GetA().GetY()-c.GetR()*c.GetR());
    if (D<0)
    {
        n.SetZ(-1);
        return n;
    }
    else
    {
        if (D>0)
        {

            k1= ((-1)* 2*(a.GetA().GetX()*a.GetV().GetX()+a.GetA().GetY()*a.GetV().GetY()-a.GetV().GetY()*c.GetA().GetY()-a.GetV().GetX()*c.GetA().GetX())+sqrt(D))/(2*(a.GetV().GetX()*a.GetV().GetX()+a.GetV().GetY()*a.GetV().GetY()));
            k2=((-1)* 2*(a.GetA().GetX()*a.GetV().GetX()+a.GetA().GetY()*a.GetV().GetY()-a.GetV().GetY()*c.GetA().GetY()-a.GetV().GetX()*c.GetA().GetX())-sqrt(D))/(2*(a.GetV().GetX()*a.GetV().GetX()+a.GetV().GetY()*a.GetV().GetY()));

            n.SetS(a.GetA()+a.GetV()*k1,a.GetA()+a.GetV()*k2,1);
            return n;
        }
        else
        {
            n.SetZ(0);
            k1= ((-1)* 2*(a.GetA().GetX()*a.GetV().GetX()+a.GetA().GetY()*a.GetV().GetY()-a.GetV().GetY()*c.GetA().GetY()-a.GetV().GetX()*c.GetA().GetX())+sqrt(D))/(2*(a.GetV().GetX()*a.GetV().GetX()+a.GetV().GetY()*a.GetV().GetY()));
            n.SetS(a.GetA()+a.GetV()*k1,a.GetA()+a.GetV()*k1,0);
            return n;
        }
    }
}

Segment operator&(const Circle& a,const Circle& b)
{
    Segment A;
    Point aa,bb,j;
    double t,h,d;
    d=sqrt((a.a.GetX()-b.a.GetX())*(a.a.GetX()-b.a.GetX()) + (a.a.GetY()-b.a.GetY())*(a.a.GetY()-b.a.GetY()));
    if (d>fabs(a.GetR()+b.GetR()))
    {
        A.SetZ(-1);
        return A;
    }
    if (d<fabs(a.GetR()-b.GetR()))
    {
        A.SetZ(-1);
        return A;
    }
    t=(a.GetR()*a.GetR()-b.GetR()*b.GetR()+d*d)/(2*d);
    if (fabs(d-(a.GetR()+b.GetR()))<0.00000000001)
    {
        t=a.GetR();
    }
    h=sqrt(a.GetR()*a.GetR()-t*t);
    j.setpoint(a.a.GetX()+t*(b.a.GetX()-a.a.GetX())/d, a.a.GetY()+t*(b.a.GetY()-a.a.GetY())/d, true);
    aa.SetX(j.GetX()+h*(b.a.GetY()-a.a.GetY())/d);
    aa.SetY(j.GetY()-h*(b.a.GetX()-a.a.GetX())/d);
    bb.SetX(j.GetX()-h*(b.a.GetY()-a.a.GetY())/d);
    bb.SetY(j.GetY()+h*(b.a.GetX()-a.a.GetX())/d);
    A.SetS(aa,bb,1);
    return A;
}
