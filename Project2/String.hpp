#ifndef JAM_STRING_HPP
#define JAM_STRING_HPP

#include <string>

class String {
  public:
    String(const String&);
    operator std::string() const;
    String& operator=(const String&);
};

bool operator==(const std::string&, const String &);
bool operator==(const String&, const std::string&);
bool operator!=(const std::string&, const String&);
bool operator!=(const String&, const std::string&);

bool operator==(const char*, const String&);
bool operator==(const String&, const char*);
bool operator!=(const char*, const String&);
bool operator!=(const String&, const char*);

std::ostream& operator<<(std::ostream&, const String&);

#endif
