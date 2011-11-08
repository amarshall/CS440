#ifndef JAM_STRING_HPP
#define JAM_STRING_HPP

#include <string>

namespace xml { class String; }

bool operator==(const std::string&, const xml::String&);
bool operator==(const xml::String&, const std::string&);
bool operator!=(const std::string&, const xml::String&);
bool operator!=(const xml::String&, const std::string&);

bool operator==(const char*, const xml::String&);
bool operator==(const xml::String&, const char*);
bool operator!=(const char*, const xml::String&);
bool operator!=(const xml::String&, const char*);

namespace xml {
  class String {
    public:
      String();
      String(const char*, int);
      String(const String&);
      operator std::string() const;
      String& operator+=(const int&);
      bool operator==(const String&) const;
      bool operator<(const String&) const;
      void append(int);
      int size();
      static int comparator(const String&, const String&);
      static int comparator(const String*, const String*);
      friend bool (::operator==)(const std::string&, const xml::String&);
      friend bool (::operator==)(const xml::String&, const std::string&);
      friend bool (::operator!=)(const std::string&, const xml::String&);
      friend bool (::operator!=)(const xml::String&, const std::string&);

      friend bool (::operator==)(const char*, const xml::String&);
      friend bool (::operator==)(const xml::String&, const char*);
      friend bool (::operator!=)(const char*, const xml::String&);
      friend bool (::operator!=)(const xml::String&, const char*);

    private:
      const char* data;
      int length;
  };
}

std::ostream& operator<<(std::ostream&, const xml::String&);

#endif
