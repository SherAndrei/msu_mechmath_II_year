#include <iomanip>
#include "doc.h"

Document::Document(double version)
  : version_(version) {}

void Document::AddTag(Tag* tag) {
  tags_.push_back(tag);
}
void Document::Print(std::ostream& out) const {
  out << std::fixed << std::setprecision(1)
      << "<?xml version=\"" << version_ << "\" encoding=\"UTF-8\"?>\n\n"
      << "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n\n";
  for (const Tag* tag : tags_) {
      tag->Print(out);
  }
  out << "</svg>\n";
}
