#include "Text.hpp"

bool xml::Text::is_Text(const Node* node) {
  return dynamic_cast<const Text*>(node) != NULL;
}

const xml::String& xml::Text::str() const {
  return *data;
}

const xml::Text* xml::Text::to_Text(const Node* node) {
  return dynamic_cast<const Text*>(node);
}
