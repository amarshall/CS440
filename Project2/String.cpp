#include <iostream>
#include <string.h>
#include "String.hpp"

xml::String::String() {
  data = NULL;
  length = 0;
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
  return strncmp(data, s.data, length) == 0;
}

#include <assert.h> //FIXME

bool operator==(const std::string&, const xml::String&) {
  assert(false);
  return false; //FIXME
}

bool operator==(const xml::String&, const std::string&) {
  return false; //FIXME
  assert(false);
}

bool operator!=(const std::string&, const xml::String&) {
  assert(false);
  return false; //FIXME
}

bool operator!=(const xml::String&, const std::string&) {
  assert(false);
  return false; //FIXME
}

bool operator==(const char*, const xml::String&) {
  assert(false);
  return false; //FIXME
}

bool operator==(const xml::String&, const char*) {
  return false; //FIXME
  assert(false);
}

bool operator!=(const char*, const xml::String&) {
  assert(false);
  return false; //FIXME
}

bool operator!=(const xml::String&, const char*) {
  assert(false);
  return false; //FIXME
}

std::ostream& operator<<(std::ostream& out, const xml::String& string) {
  out << std::string(string.data, string.length); //FIXME
  return out;
}
