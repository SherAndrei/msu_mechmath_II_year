#pragma once
#include "Point.h"

class Line
{
    Point a,v;

public:

    void SetP(double xx, double yy);
    void SetV(double xx, double yy);

    Point GetA() const;
    Point GetV() const;
    bool IsValid();
    void Setline (Point s,Point t);
    void Printline (FILE*f);
    friend Point operator&(const Line &a, const Line &b);
};
