#include <cmath>
#include <fstream>

#include "Point.h"

#define PI 3.1415926535897932384626433832795


Point::Point ()
{
	x=0;
	y=0;
	z=true;
}

void Point::SetX (double xx)
{
	x=xx;
	return;
}
void Point::SetY (double yy)
{
	y=yy;
	return;
}

void Point::SetZ (bool e)
{
	z=e;
	return;
}
void Point::setpoint (double xx,double yy, bool zz)
{
	x=xx;
	y=yy;
	z=zz;
}

bool Point::GetZ() const
{
	return z;
}

void Point::SetP(double xx, double yy)
{
	x=xx;
	y=yy;
	return;
}
double Point::GetX ()const
{
	return x;
}
double Point::GetY ()const
{
	return y;
}

void Point::Printpoint (FILE*f)
{
	fprintf(f, "plot [-0.01:0.01] %f+t,%f+t\n", x, y);
}

