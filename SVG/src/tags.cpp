#include "tags.h"

Rect::Rect(const Point& top_left, double width, double height,
           const Color& fill, const Color& stroke, double strokeWidth)
    : SimpleTag("rect", fill, stroke, strokeWidth)
    , top_left_(top_left)
    , w_(width)
    , h_(height) {
    params_ << to_str(top_left_) << ' '
            << "width = \"" << w_ << "\" "
            << "height = \"" << h_ << "\" ";
}

Circle::Circle(const Point& center, double radius,
               const Color& fill, const Color& stroke, double strokeWidth)
    : SimpleTag("circle", fill, stroke, strokeWidth)
    , c_(center)
    , r_(radius) {
    params_ << c_to_str(c_) << ' '
            << "r = \"" << r_ << "\" ";
}

Ellipse::Ellipse(const Point& center, double rx, double ry,
                 const Color& fill, const Color& stroke, double strokeWidth)
    : SimpleTag("ellipse", fill, stroke, strokeWidth)
    , c_(center), rx_(rx), ry_(ry) {}

Line::Line(const Point& p1, const Point& p2,
           const Color& fill, const Color& stroke, double strokeWidth)
    : SimpleTag("line", fill, stroke, strokeWidth)
    , a_(p1), b_(p2) {
    params_ << "x1  = \"" << a_.x << "\" " << "y1  = \"" << a_.y << "\" "
            << "x2  = \"" << b_.x << "\" " << "y2  = \"" << b_.y << "\" ";
}

static std::string points_to_str(const std::vector<Point>& points) {
    std::string result;
    for (const Point& p : points) {
        result += std::to_string(p.x) + ',' + std::to_string(p.y) + ' ';
    }
    return result;
}

Polyline::Polyline(const std::vector<Point>& points,
                    const Color& fill, const Color& stroke, double strokeWidth)
    : SimpleTag("polyline", fill, stroke, strokeWidth)
    , points_(points) {
    params_ << "points = \"" << points_to_str(points_) << "\" ";
}

Polygon::Polygon(const std::vector<Point>& points,
                 const Color& fill, const Color& stroke, double strokeWidth)
    : SimpleTag("polygon", fill, stroke, strokeWidth)
    , points_(points) {}


Text::Text(const Point& point, const std::string& text,
           const Point& offset,
           unsigned fontSize,
           const std::string& fontFamily,
           const Color& fill,
           const Color& stroke,
           double strokeWidth)
    : ComplexTag("text", fill, stroke, strokeWidth, text)
    , point_(point), offset_(offset)
    , fontSize_(fontSize), fontFamily_(fontFamily) {
    params_ << to_str(point_) << " " << d_to_str(offset_)
            << " font-family = \"" << fontFamily_ << "\" "
            << "font-size = \"" << fontSize_ << "\" ";
}
