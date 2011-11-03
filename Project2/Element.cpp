#include <list>
#include "Element.hpp"

xml::Element::Element() {
}

void xml::Element::accept(Visitor* visitor) const {
  visitor->start_element_visit(*this);
  for(std::list<Node*>::iterator it = children.begin(); it != children.end(); it++) {

  }
}
