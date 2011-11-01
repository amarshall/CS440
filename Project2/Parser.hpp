#ifndef JAM_PARSER_HPP
#define JAM_PARSER_HPP

#include "Element.hpp"

class Parser {
  public:
    Parser();
    const Element* parse(const char*, size_t);
    class ParseError {
      friend class Parser;
      public:
        ParseError(const std::string &m) : message(m) {};
        const std::string& msg() const { return message; }
      private:
        const std::string message;
        bool validTagChar(const char&);
    };

  private:
    std::stack<Element*> elementStack;
    enum { START = 1, IN_START_TAG, IN_TEXT, IN_END_TAG, FINISHED } state;
    // enum { START = 1, IN_TAG_NAME, IN_TAG_NAMESPACE_NAME, IN_TAG_NAMESPACE_URI, CLOSE } elementState;
};

#endif
