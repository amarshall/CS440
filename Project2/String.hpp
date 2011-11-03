#ifndef JAM_STRING_HPP
#define JAM_STRING_HPP

#include <string>

namespace xml {
  class String {
    public:
      String();
      String(const char*, int);
      String(const String&);
      operator std::string() const;
      String& operator+=(const int&);
      bool operator==(const String&);
      void append(int);
      int size();

    private:
      const char* data;
      int length;
  };
}

bool operator==(const std::string&, const xml::String&);
bool operator==(const xml::String&, const std::string&);
bool operator!=(const std::string&, const xml::String&);
bool operator!=(const xml::String&, const std::string&);

bool operator==(const char*, const xml::String&);
bool operator==(const xml::String&, const char*);
bool operator!=(const char*, const xml::String&);
bool operator!=(const xml::String&, const char*);

std::ostream& operator<<(std::ostream&, const xml::String&);

#endif
