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

bool operator==(const std::string& s, const xml::String& S) {
  return (std::string)S == s;
}

bool operator==(const xml::String& S, const std::string& s) {
  return (std::string)S == s;
}

bool operator!=(const std::string& s, const xml::String& S) {
  return (std::string)S != s;
}

bool operator!=(const xml::String& S, const std::string& s) {
  return (std::string)S != s;
}

bool operator==(const char* c, const xml::String& S) {
  return strncmp(S.data, c, S.length) == 0;
}

bool operator==(const xml::String& S, const char* c) {
  return strncmp(S.data, c, S.length) == 0;
}

bool operator!=(const char* c, const xml::String& S) {
  return strncmp(S.data, c, S.length) != 0;
}

bool operator!=(const xml::String& S, const char* c) {
  return strncmp(S.data, c, S.length) != 0;
}

std::ostream& operator<<(std::ostream& out, const xml::String& string) {
  out << std::string(string);
  return out;
}
