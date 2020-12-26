#pragma once
#include <ostream>
#include <string>
#include <vector>
#include "tag.h"

class Document {
 private:
  double version_;
  std::vector<Tag*> tags_;
 public:
  explicit Document(double version = 1.0);

  void AddTag(Tag* obj);
  void Print(std::ostream& out) const;
};
