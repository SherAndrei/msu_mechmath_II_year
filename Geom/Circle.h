#pragma once
#include "Point.h"
#include "Segment.h"

class Circle
{
    Point a;
    double r;

public:
    void SetC (Point aa, double rr);

    Point  GetA() const;
    double GetR() const;

    bool IsValid ();
    friend Segment operator&(const Circle &a, const Circle &b);

    void Printcircle(FILE*f);
};
