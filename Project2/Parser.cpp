#include <stack>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "Element.hpp"
#include "Parser.hpp"
#include "Text.hpp"

xml::Parser::Parser() {
  state = START;
  root = NULL;
  accumulator = NULL;
}

bool xml::Parser::validTagChar(const char& c) {
  return isalnum(c) || c == '_';
}

bool xml::Parser::validTextChar(const char& c) {
  return c != '<' && c != '>';
}

bool xml::Parser::validURIChar(const char& c) {
  return c != '"';
}

void xml::Parser::saveElement(Element* element) {
  if(element->tagNamespaceId == NULL) {
    element->tagNamespaceId = new String();
    element->tagNamespace = new String();
  } else {
    element->tagNamespace = new String((*namespaceStack.top())[*element->tagNamespaceId]);
  }
  if(nodeStack.size()) nodeStack.top()->children.push_back(element);
  nodeStack.push(element);
  accumulator = NULL;
}

void xml::Parser::saveText(Text* text) {
  text->data = accumulator;
  if(nodeStack.size()) nodeStack.top()->children.push_back(text);
  accumulator = NULL;
}

void xml::Parser::requestNewAccumulator(const char* pos) {
  if(accumulator == NULL) accumulator = new String(pos, 0);
}

const xml::Element* xml::Parser::parse(const char* data, size_t dataSize) {
  state = START;
  Node* node = new Element();
  bool whitespace = false;
  String* lastAccumulator; // WARNING: This isn't always the last one, just when needed.

  for(unsigned int i = 0; i < dataSize; ++i) {
    const char c = data[i];
    if(c == EOF) break;

    while(true) {
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
            if(nodeStack.size() == 0) {
              state = FINISHED;
              continue;
            } else if(c == '<') {
              node = new Element();
              state = IN_TAG;
            } else {
              node = new Text();
              state = IN_TEXT;
              continue;
            }
            break;

          case IN_TAG:
            if(c == '/') {
              state = IN_END_TAG_NS_NAME;
            } else {
              state = IN_START_TAG_NS_NAME;
              std::map<const String, String>* map;
              if(namespaceStack.size() == 0) {
                map = new std::map<const String, String>;
              } else {
                map = new std::map<const String, String>(*namespaceStack.top());
              }
              namespaceStack.push(map);
              continue;
            }
            break;

          case IN_START_TAG_NS_NAME:
            requestNewAccumulator(data + i);
            if(c == ':' && accumulator->size() != 0) {
              //TODO: Check namespace is defined.
              dynamic_cast<Element*>(node)->tagNamespaceId = accumulator;
              accumulator = NULL;
              state = IN_START_TAG_NAME;
            } else if(isspace(c) || c == '>') {
              state = IN_START_TAG_NAME;
              continue;
            } else if(validTagChar(c)) {
              accumulator->append(1);
            } else {
              throw ParseError("Invalid tag name/namespace.");
            }
            break;

          case IN_START_TAG_NAME:
            requestNewAccumulator(data + i);
            if(validTagChar(c)) {
              accumulator->append(1);
            } else if(isspace(c) || c == '>') {
              dynamic_cast<Element*>(node)->tagName = accumulator;
              accumulator = NULL;
              state = IN_START_TAG;
              continue;
            } else {
              throw ParseError("Invalid tagname.");
            }
            break;

          case IN_START_TAG:
            if(isspace(c)) {
              // Continue
            } else if(validTagChar(c)) {
              state = IN_TAG_NS_DEF;
              continue;
            } else if(c == '>') {
              saveElement((Element*)node);
              state = IN_DOC;
            } else {
              throw ParseError("Invalid tag inner text.");
            }
            break;

          case IN_TAG_NS_DEF:
            requestNewAccumulator(data + i);
            if(validTagChar(c)) {
              accumulator->append(1);
            } else if(c == ':' && *accumulator == "xmlns") {
              delete accumulator;
              accumulator = NULL;
              state = IN_TAG_NS_LVAL;
            } else {
              throw ParseError("Invalid tag inner text (NSdef).");
            }
            break;

          case IN_TAG_NS_LVAL:
            requestNewAccumulator(data + i);
            if(validTagChar(c)) {
              accumulator->append(1);
            } else if(c == '=') {
              lastAccumulator = accumulator;
              accumulator = NULL;
              state = IN_TAG_NS_EQUALS;
            } else {
              throw ParseError("Invalid tag inner text (NSname).");
            }
            break;

          case IN_TAG_NS_EQUALS:
            if(c == '"') {
              state = IN_TAG_NS_RVAL;
            } else {
              throw ParseError("Invalid namespace definition.");
            }
            break;

          case IN_TAG_NS_RVAL:
            requestNewAccumulator(data + i);
            if(validURIChar(c)) {
              accumulator->append(1);
            } else if(c == '"') {
              (*namespaceStack.top())[*lastAccumulator] = *accumulator;
              delete lastAccumulator;
              lastAccumulator = NULL;
              delete accumulator;
              accumulator = NULL;
              state = IN_START_TAG;
            } else {
              throw ParseError("Invalid NS URI.");
            }
            break;

          case IN_END_TAG_NS_NAME:
            requestNewAccumulator(data + i);
            if(c == ':' && accumulator->size() != 0 && nodeStack.top()->nmspaceId() == *accumulator) {
              delete accumulator;
              accumulator = NULL;
              state = IN_END_TAG_NAME;
            } else if(isspace(c) || c == '>') {
              state = IN_END_TAG_NAME;
              continue;
            } else if(validTagChar(c)) {
              accumulator->append(1);
            } else {
              throw ParseError("Invalid/mismatched end tag name/namespace.");
            }
            break;

          case IN_END_TAG_NAME:
            requestNewAccumulator(data + i);
            if(isspace(c)) {
              // Continue;
            } else if(validTagChar(c) && !whitespace) {
              accumulator->append(1);
            } else if(isspace(c) || c == '>') {
              state = IN_END_TAG;
              continue;
            } else {
              throw ParseError("Invalid end tag inner text.");
            }
            break;

          case IN_END_TAG:
            if(isspace(c)) {
              // Continue
            } else if(c == '>' && nodeStack.top()->name() == *accumulator) {
              nodeStack.pop();
              delete namespaceStack.top();
              namespaceStack.pop();
              delete accumulator;
              accumulator = NULL;
              delete node;
              node = NULL;
              state = IN_DOC;
            } else {
              throw ParseError("Invalid/mismatched end tag.");
            }
            break;

          case IN_TEXT:
            if(nodeStack.size() == 0) throw ParseError("Text outside root.");
            requestNewAccumulator(data + i);
            if(c == '<') {
              saveText((Text*)node);
              state = IN_DOC;
              continue;
            } else if(validTextChar(c)) {
              accumulator->append(1);
            } else {
              throw ParseError("Bad text.");
            }
            break;

          case FINISHED:
            if(!isspace(c)) throw ParseError("Text outside root.");
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

  delete accumulator;
  accumulator = NULL;
  while(!namespaceStack.empty()) namespaceStack.pop();

  return root;
}
