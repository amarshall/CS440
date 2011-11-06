#ifndef JAM_TEXT_HPP
#define JAM_TEXT_HPP

#include "Node.hpp"
#include "String.hpp"

namespace xml {
  class Text : public Node {
    friend class Parser;

    public:
      const String& str() const;
      static bool is_Text(const Node*);
      static const Text* to_Text(const Node*);

    private:
      String* data;
  };
}

#endif
