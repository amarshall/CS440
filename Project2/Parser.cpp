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

void xml::Parser::saveElement(Node*& node, String*& tagName) {
  std::cout << "Saving element with name " << tagName << std::endl;
  Element* element = dynamic_cast<Element*>(node);
  element->tagName = tagName;
  nodeStack.push(element);
  if(nodeStack.size()) nodeStack.top()->children.push_back(node);
  node = new Node();
  tagName = new String();
}

void xml::Parser::saveText(Node*& node, String*& text) {
  std::cout << "Saving text with text " << text << std::endl;
  dynamic_cast<Text*>(node)->data = text;
  if(nodeStack.size()) nodeStack.top()->children.push_back(node);
  node = new Node();
  text = new String();
}

const xml::Element* xml::Parser::parse(const char* data, size_t dataSize) {
  Node* node;
  String* accumulator;
  bool whitespace = false;

  for(int i = 0; i < dataSize; ++i) {
    const char c = data[i];
    if(c == EOF) break;

    while(true) {
      try {
        switch(state) {
          case START:
            if(isspace(c)) {
              // Continue
            } else if(c == '<') {
              node = root = new Element();
              accumulator = new String();
              state = IN_TAG;
            } else {
              throw ParseError("Text outside root.");
            }
            break;

          case IN_DOC:
            if(isspace(c)) {
            } else if(c == '<') {
              accumulator = NULL;
              state = IN_TAG;
            } else {
              accumulator = new String(data + i, 1);
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
              std::cout << "Closing tag for " << accumulator << std::endl;
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
