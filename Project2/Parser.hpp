#ifndef JAM_PARSER_HPP
#define JAM_PARSER_HPP

#include <stack>
#include "Element.hpp"

namespace xml {
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
      };

    private:
      Element* root;
      std::stack<Element*> nodeStack;
      enum { START = 1, IN_DOC, IN_TAG, IN_START_TAG, IN_TEXT, IN_END_TAG, FINISHED } state;
      // enum { START = 1, IN_TAG_NAME, IN_TAG_NAMESPACE_NAME, IN_TAG_NAMESPACE_URI, CLOSE } elementState;
      void saveElement(Node*&, String*&);
      void saveText(Node*&, String*&);
      bool validTagChar(const char&);
      bool validTextChar(const char&);
  };
}

#endif
