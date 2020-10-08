#pragma once

class Point
{
    double x,y;
    bool z;
public:

    Point ();
    void setpoint (double xx,double yy, bool zz);
    void SetP(double xx, double yy);
    void SetX (double xx);
    void SetY (double yy);
    void SetZ (bool e);

    bool GetZ()const;
    double GetX ()const;
    double GetY ()const;

    Point operator+(const Point&)const;
    friend Point operator*(const Point &a, double z);
    void Printpoint (FILE*f);
};
