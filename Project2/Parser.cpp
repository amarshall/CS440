#include <assert.h>
#include <stack>
#include <iostream>
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

void xml::Parser::saveElement(Element* element) {
  std::cerr << "Saving node with name: " << *accumulator;
  if(nodeStack.size()) std::cerr << " as child of " << *nodeStack.top()->tagName;
  std::cerr << std::endl;

  element->tagName = accumulator;
  if(nodeStack.size()) nodeStack.top()->children.push_back(element);
  if(nodeStack.size()) assert(nodeStack.top()->children.back() != NULL);
  nodeStack.push(element);
  accumulator = NULL;
}

void xml::Parser::saveText(Text* text) {
  std::cerr << "Saving text: " << *accumulator;
  if(nodeStack.size()) std::cerr << " as child of " << *nodeStack.top()->tagName;
  std::cerr << std::endl;

  text->data = accumulator;
  if(nodeStack.size()) nodeStack.top()->children.push_back(text);
  assert(nodeStack.top()->children.back() != NULL);
  accumulator = NULL;
}

void xml::Parser::requestNewAccumulator(const char* pos) {
  if(accumulator == NULL) accumulator = new String(pos, 0);
}

const xml::Element* xml::Parser::parse(const char* data, size_t dataSize) {
  Node* node = new Element();
  bool whitespace = false;

  for(unsigned int i = 0; i < dataSize; ++i) {
    const char c = data[i];
    if(c == EOF) break;

    while(true) {
      // std::cerr << "STATE: " << state << " | Stack: " << nodeStack.size();
      // if(accumulator != NULL) std::cerr << " | Accumulator: " << *accumulator;
      // std::cerr << std::endl;
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
              state = IN_END_TAG;
            } else {
              state = IN_START_TAG;
              continue;
            }
            break;

          case IN_START_TAG:
            requestNewAccumulator(data + i);
            if(validTagChar(c) && !whitespace) {
              accumulator->append(1);
            } else if(isspace(c)) {
              // Continue
            } else if(c == '>' && accumulator->size() != 0) {
              saveElement((Element*)node);
              state = IN_DOC;
            } else {
              throw ParseError("Invalid tag inner text.");
            }
            break;

          case IN_END_TAG:
            requestNewAccumulator(data + i);
            if(validTagChar(c) && !whitespace) {
              accumulator->append(1);
            } else if(isspace(c)) {
              // Continue
            } else if(c == '>' && accumulator->size() != 0) {
              if(*nodeStack.top()->tagName == *accumulator) {
                nodeStack.pop();
                accumulator = NULL;
                state = IN_DOC;
              } else {
                throw ParseError("Open/close tag mismatch.");
              }
            } else {
              throw ParseError("Invalid tag inner text.");
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

  for(unsigned int i = 0; i < root->n_children(); ++i) {
    std::cerr << "root child: " << root->child(i) << std::endl;
  }

  return root;
}
