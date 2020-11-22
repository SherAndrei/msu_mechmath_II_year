#include "color.h"

Color::Color(const std::string& color)
    : color_("\"" + color + "\"") {}

Color::Color(int red, int green, int blue)
    : color_("\"rgb(" + std::to_string(red)
             + ','  + std::to_string(green)
             + ','  + std::to_string(blue) + ")\"") {}

std::string Color::str() const {
    return color_;
}
