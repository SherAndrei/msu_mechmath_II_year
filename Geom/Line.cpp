#include <cmath>
#include <fstream>
#include "Line.h"
#include "Point.h"

void Line::SetP(double xx, double yy)
{
	a.SetX(xx);
	a.SetY(yy);
	return;
}
void Line::SetV(double xx, double yy)
{
	v.SetX(xx);
	v.SetY(yy);
	return;
}

Point Line::GetA() const
{
	return a;
}

Point Line::GetV() const
{
	return v;
}

bool Line::IsValid()
{
	return (fabs(v.GetX())>0.00000001||fabs(v.GetY())>0.00000001);
}

void Line::Setline (Point s,Point t)
{
	a=s;
	v.SetP(s.GetX()+(-1)*t.GetX(), s.GetY()+(-1)*t.GetY());
}
void Line::Printline (FILE*f)
{
	fprintf (f,"%lf ",a.GetX()-v.GetX());
	fprintf (f,"%lf\n",a.GetY()-v.GetY());
	fprintf (f,"%lf ",a.GetX()+v.GetX());
	fprintf (f,"%lf\n",a.GetY()+v.GetY());
}