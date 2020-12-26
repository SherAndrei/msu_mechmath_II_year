#pragma once
#include <string>

struct Point {
  double x;
  double y;
};

std::string to_str(const Point& p);
std::string c_to_str(const Point& c);
std::string d_to_str(const Point& d);
