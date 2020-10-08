#pragma once
#include "Point.h"
#include <fstream>

class Segment
{
    Point a,b;
    int z;
public:

    Segment ();
    void Setseg(Point aa,Point bb);
    void SetS (Point aa,Point bb, int zz);
    void SetZ(int x);
    
	Point GetA();
    Point GetB();
    int GetZ();
    
	double Length ();
    void Printsegment(FILE*f);
};
