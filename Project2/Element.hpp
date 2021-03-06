#ifndef JAM_ELEMENT_HPP
#define JAM_ELEMENT_HPP

#include <list>
#include "Node.hpp"
#include "String.hpp"

namespace xml {
  class Visitor;

  class Element : public Node {
    friend class Parser;

    public:
      Element();
      ~Element();
      const String& name() const;
      const String& nmspace() const;
      const String& nmspaceId() const;
      size_t n_children() const;
      const Node* child(size_t) const;
      void accept(Visitor*) const;
      static bool is_Element(const Node*);
      static const Element *to_Element(const Node*);

    private:
      String* tagName;
      const String* tagNamespace;
      String* tagNamespaceId;
      std::list<Node*> children;
  };
}

#include "Visitor.hpp"

#endif
