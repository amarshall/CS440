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

xml::String::String(const String& s) {
  data = s.data;
  length = s.length;
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

int xml::String::comparator(const String& a, const String& b) {
  return a < b;
}

int xml::String::comparator(const String* a, const String* b) {
  return *a < *b;
}

bool xml::String::operator==(const String& s) const {
  return strncmp(data, s.data, length) == 0;
}

bool xml::String::operator<(const String& s) const {
  return strncmp(data, s.data, length) < 0;
}

#include <assert.h> //FIXME

bool operator==(const std::string&, const xml::String&) {
  assert(false);
  return false; //FIXME
}

bool operator==(const xml::String& S, const std::string& s) {
  assert(false);
  return (std::string)S == s;
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

bool operator==(const xml::String& S, const char* c) {
  assert(false);
  return strncmp(S.data, c, S.length) == 0;
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
