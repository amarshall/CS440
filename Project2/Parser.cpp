#include <stack>
#include <iostream>
#include <string>
#include "Element.hpp"
#include "Parser.hpp"
#include "Text.hpp"

xml::Parser::Parser() {
  state = START;
  root = NULL;
}

bool xml::Parser::validTagChar(const char& c) {
  return isalnum(c) || c == '_';
}

bool xml::Parser::validTextChar(const char& c) {
  return c != '<' && c != '>';
}

void xml::Parser::saveElement(Node* node, String*& tagName) {
  std::cerr << "Saving node with name: " << *tagName << std::endl;
  Element* element = dynamic_cast<Element*>(node);
  element->tagName = tagName;
  nodeStack.push(element);
  if(nodeStack.size()) nodeStack.top()->children.push_back(node);
}

void xml::Parser::saveText(Node* node, String*& text) {
  std::cerr << "Saving text: " << *text << std::endl;
  dynamic_cast<Text*>(node)->data = text;
  if(nodeStack.size()) nodeStack.top()->children.push_back(node);
}

void xml::Parser::requestNewAccumulator(String* accumulator, const char* pos) {
  if(accumulator == NULL) accumulator = new String(pos, 0);
}

const xml::Element* xml::Parser::parse(const char* data, size_t dataSize) {
  Node* node = new Element();
  String* accumulator = NULL;
  bool whitespace = false;

  for(unsigned int i = 0; i < dataSize; ++i) {
    const char c = data[i];
    if(c == EOF) break;

    while(true) {
      std::cerr << "STATE: " << state;
      if(accumulator != NULL) std::cerr << " | Accumulator: " << *accumulator;
      std::cerr << std::endl;
      try {
        switch(state) {
          case START:
            if(isspace(c)) {
              // Continue
            } else if(c == '<') {
              root = dynamic_cast<Element*>(node);
              state = IN_TAG;
            } else {
              throw ParseError("Text outside root.");
            }
            break;

          case IN_DOC:
            if(isspace(c)) {
            } else if(c == '<') {
              accumulator = NULL;
              node = new Element();
              state = IN_TAG;
            } else {
              node = new Text();
              state = IN_TEXT;
            }
            break;

          case IN_TAG:
            if(c == '/') {
              state = IN_END_TAG;
            } else {
              state = IN_START_TAG;
              continue;
            }
            break;

          case IN_START_TAG:
            requestNewAccumulator(accumulator, data + i);
            if(validTagChar(c) && !whitespace) {
              accumulator->append(1);
            } else if(isspace(c)) {
              // Continue
            } else if(c == '>' && accumulator->size() != 0) {
              saveElement(node, accumulator);
              state = IN_DOC;
            } else {
              throw ParseError("Invalid tag inner text.");
            }
            break;

          case IN_END_TAG:
            if(validTagChar(c) && !whitespace) {
              accumulator->append(1);
            } else if(isspace(c)) {
              // Continue
            } else if(c == '>' && accumulator->size() != 0) {
              if(nodeStack.top()->tagName == accumulator) {
                nodeStack.pop();
              } else {
                throw ParseError("Open/close tag mismatch.");
              }
            } else {
              throw ParseError("Invalid tag inner text.");
            }
            break;

          case IN_TEXT:
            if(c == '<') {
              saveText(node, accumulator);
              state = IN_TAG;
            } else if(validTextChar(c)) {
              accumulator->append(1);
            }
            break;

          case FINISHED:
            break;
        }
      } catch(const Parser::ParseError &e) {
        std::cerr << e.msg() << std::endl;
        exit(1);
      }
      whitespace = isspace(c);
      break;
    }
  }
  if(nodeStack.size() != 0) throw ParseError("Unclosed tags.");

  return root;
}
