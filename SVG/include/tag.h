#pragma once
#include <ostream>
#include <sstream>
#include <string>
#include "color.h"

class Tag {
 protected:
  std::string name_;
  Color fillColor_;
  Color strokeColor_;
  double strokeWidth_;
  std::ostringstream params_;

 protected:
  explicit Tag(const std::string& name,
               const Color& fill,
               const Color& stroke,
               double strokeWidth);

 public:
  virtual void Print(std::ostream& out) const = 0;
};

/*
<name_ params_ />
*/
class SimpleTag : public Tag {
 protected:
  using Tag::Tag;

 public:
  void Print(std::ostream& out) const override;
};

/*
<name_ params_>
  contents_
</name>
*/
class ComplexTag : public Tag {
 protected:
  std::string contens_;

 protected:
  explicit ComplexTag(const std::string& name,
                      const Color& fill,
                      const Color& stroke,
                      double strokeWidth,
                      const std::string& contents);
 public:
  void Print(std::ostream& out) const override;
};


