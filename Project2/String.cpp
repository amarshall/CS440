#include "String.hpp"

String::String(const std::string& s) {
  data = s;
}

String& String::operator=(const String& s) {
  data = s.data;
  return *this;
}

String & String::operator+=(const std::string& s) {
  data += s;
  return *this;
}

String & String::operator+=(const char& c) {
  data += c;
  return *this;
}
