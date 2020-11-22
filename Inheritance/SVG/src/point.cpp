#include "point.h"

std::string to_str(const Point& p) {
    return "x = \"" + std::to_string(p.x) + "\" y = \"" + std::to_string(p.y) + "\"";
}

std::string c_to_str(const Point& p) {
    return "cx = \"" + std::to_string(p.x) + "\" cy = \"" + std::to_string(p.y) + "\"";
}

std::string d_to_str(const Point& p) {
    return "dx = \"" + std::to_string(p.x) + "\" dy = \"" + std::to_string(p.y) + "\"";
}
