#pragma once
#include <fstream>
#include <cmath>
#include "Point.h"
#include "Segment.h"

void Segment::Setseg(Point aa,Point bb)
{
	a=aa;
	b=bb;
}

Segment::Segment ()
{
	a.SetP(0,0);
	b.SetP(1,0);
	z=1;
}
Point Segment::GetA()
{
	return a;
}
Point Segment::GetB()
{
	return b;
}
void Segment::SetS (Point aa,Point bb, int zz)
{
	a=aa;
	b=bb;
	z=zz;
	return;
}

void Segment::SetZ(int x)
{
	z=x;
	return;
}
int Segment::GetZ()
{
	return z;
}

double Segment::Length ()
{
	double h;
	h = sqrt ((a.GetX()-b.GetX())*(a.GetX()-b.GetX())+(a.GetY()-b.GetY())*(a.GetY()-b.GetY()));
	return h;
}

void Segment::Printsegment(FILE*f)
{
	fprintf(f, "%lf ",a.GetX());
	fprintf(f, "%lf\n",a.GetY());
	fprintf(f, "%lf ",b.GetX());
	fprintf(f, "%lf\n",b.GetY());
	fprintf(f,"         \n");
}
