#include "String.hpp"

xml::String::String() {
  data = NULL;
  length = NULL;
}

xml::String::String(const char* d, int l) {
  data = d;
  length = l;
}

xml::String::operator std::string() const {
  return std::string(data, length);
}

xml::String& xml::String::operator+=(const int& l) {
  length += l;
  return *this;
}

void xml::String::append(int i) {
  length += i;
}

int xml::String::size() {
  return length;
}

bool xml::String::operator==(const String& s) {
  return ((const std::string)s).compare(0, length, data) == 0;
}
