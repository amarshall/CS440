#include <list>
#include "Element.hpp"

xml::Element::Element() {
  tagName = NULL;
  tagNamespace = NULL;
  tagNamespaceId = NULL;
}

xml::Element::~Element() {
  delete tagName;
  // delete tagNamespace; // TODO: auto_ptr
  delete tagNamespaceId;
  for(std::list<Node*>::iterator it = children.begin(); it != children.end(); ++it) {
    delete *it;
  }
}

const xml::String& xml::Element::name() const {
  return *tagName;
}

const xml::String& xml::Element::nmspace() const {
  return *tagNamespace;
}

const xml::String& xml::Element::nmspaceId() const {
  return *tagNamespaceId;
}

size_t xml::Element::n_children() const {
  return children.size();
}

const Node* xml::Element::child(size_t n) const {
  std::list<Node*>::const_iterator it = children.begin();
  std::advance(it, n);
  return *it;
}

void xml::Element::accept(Visitor* visitor) const {
  visitor->start_element_visit(*this);
  for(std::list<Node*>::const_iterator it = children.begin(); it != children.end(); it++) {
    if(Element::is_Element(*it)) {
      dynamic_cast<Element*>(*it)->accept(visitor);
    } else if(xml::Text::is_Text(*it)) {
      visitor->visit_text(*dynamic_cast<Text*>(*it));
    }
  }
  visitor->end_element_visit(*this);
}

bool xml::Element::is_Element(const Node* node ) {
  return dynamic_cast<const xml::Element*>(node) != NULL;
}

const xml::Element* xml::Element::to_Element(const Node* node) {
  return dynamic_cast<const Element*>(node);
}
