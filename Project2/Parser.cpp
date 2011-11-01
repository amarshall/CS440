#include <stack>
#include <iostream>
#include <string>
#include "Element.hpp"
#include "Parser.hpp"

Parser::Parser() {
  state = START;
}

bool validTagChar(const char& c) {
  return isalnum(c) || c == '_';
}

const Element* Parser::parse(const char* data, size_t dataSize) {
  Node* node;
  for(int i = 0; i < dataSize; ++i) {
    const char c = data[i];
    if(c == EOF) break;

    try {
      switch(state) {
        case START:
          if(isspace(c)) {
            // Continue
          } else if(c == '<') {
            // TODO: save and store previous node;
            state = IN_START_TAG;
            node = new Element();
          } else {
            throw ParseError("Text outside root.");
          }
          break;

        case IN_START_TAG:
          if(isspace(c)) {
            // Continue
          } else if(validTagChar(c)) {
            ((Element*)node)->tagName += c;
          } else {
            throw ParseError("Invalid tag inner text.");
          }
      }
    } catch(const Parser::ParseError &e) {
      std::cerr << e.msg() << std::endl;
      exit(1);
    }
  }
}
