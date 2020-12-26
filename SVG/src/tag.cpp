#include <iomanip>
#include "tag.h"

Tag::Tag(const std::string& name, const Color& fill,
         const Color& stroke, double strokeWidth)
    : name_(name), fillColor_(fill)
    , strokeColor_(stroke), strokeWidth_(strokeWidth) {
    params_ << std::fixed << std::setprecision(1)
            << "fill = "   << fillColor_.str() << ' '
            << "stroke = " << strokeColor_.str() << ' '
            << "stroke-width = \"" << strokeWidth_ << "\" ";
}

ComplexTag::ComplexTag(const std::string& name,
                      const Color& fill,
                      const Color& stroke,
                      double strokeWidth,
                      const std::string& contents)
    : Tag(name, fill, stroke, strokeWidth)
    , contens_(contents) {}

void SimpleTag::Print(std::ostream& out) const {
    out << '<' << name_ << ' ' << params_.str() << "/>\n";
}

void ComplexTag::Print(std::ostream& out) const {
    out << '<' << name_ << ' ' << params_.str() << ">\n"
        << contens_ << '\n'
        << "</" << name_ << ">\n\n";
}
