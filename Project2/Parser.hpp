#ifndef JAM_PARSER_HPP
#define JAM_PARSER_HPP

#include <map>
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
      String* accumulator;
      std::stack<Element*> nodeStack;
      std::stack<std::map<String, String*>*> namespaceStack;
      enum {
        /*  1 */ START = 1,
        /*  2 */ IN_DOC,
        /*  3 */ IN_TAG,
        /*  4 */ IN_START_TAG_NS_NAME,
        /*  5 */ IN_START_TAG_NAME,
        /*  6 */ IN_START_TAG,
        /*  7 */ IN_TAG_NS_DEF,
        /*  8 */ IN_TAG_NS_LVAL,
        /*  9 */ IN_TAG_NS_EQUALS,
        /* 10 */ IN_TAG_NS_RVAL,
        /* 11 */ IN_TEXT,
        /* 12 */ IN_END_TAG_NS_NAME,
        /* 13 */ IN_END_TAG_NAME,
        /* 14 */ IN_END_TAG,
        /* 15 */ FINISHED
      } state;
      void saveElement(Element*);
      void saveText(Text*);
      bool validTagChar(const char&);
      bool validTextChar(const char&);
      bool validURIChar(const char&);
      void requestNewAccumulator(const char*);
  };
}

#endif
