#include <cmath>
#include <fstream>
#include "Circle.h"

#define PI 3.1415926535897932384626433832795


void Circle::SetC (Point aa, double rr)
{
	a.SetP(aa.GetX(),aa.GetY());
	r=rr;
	return;
}

Point Circle::GetA() const
{
	return a;
}
double Circle::GetR() const
{
	return r;
}

bool Circle::IsValid ()
{
	return r > 0;
}

void Circle::Printcircle(FILE*f)
{
	double yy;
	Point s;
	int i;
	s.setpoint(r,0,1);
	yy=2*PI/1000;
	for (i=1;i<1001;i++)
	{
		s.setpoint (a.GetX()+r*cos(yy*i),a.GetY()+r*sin(yy*i),1 );
		fprintf(f,"%lf ",s.GetX());
		fprintf(f,"%lf\n",s.GetY());
	}
	fprintf(f,"         \n");
	return;
}
