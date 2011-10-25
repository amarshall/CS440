#ifndef JAM_TEXT_HPP
#define JAM_TEXT_HPP

class Text : public Node {
  public:
    const String& str() const;
    static bool is_Text(const Node*);
    static const Text* to_Text(const Node*);
};

#endif
