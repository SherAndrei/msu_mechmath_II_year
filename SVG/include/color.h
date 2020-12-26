#pragma once
#include <string>
#include <ostream>

class Color {
 private:
  std::string color_;
 public:
  explicit Color(const std::string& color);
  Color(int red, int green, int blue);

  std::string str() const;
};
