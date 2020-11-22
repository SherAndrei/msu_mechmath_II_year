#pragma once
#include <string>
#include <vector>
#include "point.h"
#include "color.h"
#include "tag.h"

class Rect : public SimpleTag {
 private:
  Point top_left_;
  double w_;
  double h_;

 public:
  Rect(const Point& top_left, double width, double height,
       const Color& fill = Color("white"),
       const Color& stroke = Color("black"),
       double strokeWidth = 1.0);
};

class Circle : public SimpleTag {
 private:
  Point  c_;
  double r_;

 public:
  Circle(const Point& center, double radius,
         const Color& fill   = Color("white"),
         const Color& stroke = Color("black"),
         double strokeWidth  = 1.0);
};

class Ellipse : public SimpleTag {
 private:
  Point  c_;
  double rx_;
  double ry_;

 public:
  Ellipse(const Point& center, double rx, double ry,
          const Color& fill   = Color("white"),
          const Color& stroke = Color("black"),
          double strokeWidth  = 1.0);
};

class Line : public SimpleTag {
 private:
  Point a_, b_;

 public:
  Line(const Point& a, const Point& b,
       const Color& fill   = Color("white"),
       const Color& stroke = Color("black"),
       double strokeWidth  = 1.0);
};

class Polyline : public SimpleTag {
 private:
  std::vector<Point> points_;

 public:
  explicit Polyline(const std::vector<Point>& points,
                    const Color& fill   = Color("white"),
                    const Color& stroke = Color("black"),
                    double strokeWidth  = 1.0);
};

class Polygon : public SimpleTag {
 private:
  std::vector<Point> points_;

 public:
  explicit Polygon(const std::vector<Point>& points,
                   const Color& fill   = Color("white"),
                   const Color& stroke = Color("black"),
                   double strokeWidth  = 1.0);
};

class Text : public ComplexTag {
 private:
  Point point_;
  Point offset_;
  unsigned fontSize_;
  std::string fontFamily_;

 public:
  Text(const Point& point, const std::string& text,
       const Point& offset = {0, 0},
       unsigned fontSize = 14,
       const std::string& fontFamily = "Verdana",
       const Color& fill   = Color("white"),
       const Color& stroke = Color("black"),
       double strokeWidth  = 1.0);
};
