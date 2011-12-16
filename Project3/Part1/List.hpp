#include <stdlib.h>

namespace cs540 {
  template <typename T>
  class List {
    private:
      class Node {
        public:
          Node();
          Node(const T&);
          T object;
          Node* prev;
          Node* next;
      };
      Node sentinel;
      size_t _size;

    public:
      class Iterator {
        friend class List;
        public:
          Iterator(List&);
          virtual Iterator& operator++() { node = node->next; return *this; }
          virtual Iterator operator++(int) { node = node->next; return *this; }
          virtual Iterator& operator--() { node = node->prev; return *this; }
          virtual Iterator operator--(int) { node = node->prev; return *this; }
          T& operator*() const { return node->object; };
          T* operator->() const { return &(node->object); };
          virtual bool operator==(const Iterator&);
          virtual bool operator!=(const Iterator&);

        protected:
          Node* node;

        private:
          Iterator(Node* n) : node(n) {};
          Iterator(const Node* n) : node(n) {};
      };

      class ConstIterator : public Iterator {
        friend class List;
        public:
          ConstIterator(const Iterator& o) : Iterator(o.node) {}
          const T& operator*() const { return this->node->object; };
          const T* operator->() const { return &(this->node->object); };

        private:
          ConstIterator(Node* n) : Iterator(n) {}
          ConstIterator(const Node* n) : Iterator(n) {}
      };

      class ReverseIterator : public Iterator {
        friend class List;
        public:
          ReverseIterator(const ReverseIterator& o) : Iterator(o.node) {}
          T& operator*() const { return this->node->object; };
          T* operator->() const { return &(this->node->object); };

        private:
          ReverseIterator(Node* n) : Iterator(n) {}
      };

      List() : _size(0) {}
      List(const List&);
      List& operator=(const List&);
      size_t size() const { return _size; }

      Iterator begin() { return Iterator(sentinel.next); }
      Iterator end() { return Iterator(&sentinel); }

      ConstIterator begin() const { return ConstIterator(sentinel.next); }
      ConstIterator end() const { return ConstIterator(const_cast<Node*>(&sentinel)); }

      ReverseIterator rbegin() { return ReverseIterator(sentinel.prev); }
      ReverseIterator rend() { return ReverseIterator(&sentinel); }

      T& front() { return *(begin()); }
      T& back() { return *(--end()); }
      const T& front() const { return *(begin()); }
      const T& back() const { return *(--end()); }

      void push_front(const T& obj) { insert(begin(), obj); }
      void push_back(const T& obj) { insert(end(), obj); }

      void pop_front() { erase(begin()); }
      void pop_back() { erase(--end()); }

      Iterator insert(Iterator pos, const T&);
      template <typename IT_T> void insert(Iterator pos, IT_T rangeBegin, IT_T rangeEnd);

      Iterator erase(Iterator pos) { return erase(pos, ++pos); };
      Iterator erase(Iterator rangeBegin, Iterator rangeEnd) {
        Node* nodeBegin = rangeBegin.node->prev;
        Node* nodeEnd = rangeEnd.node;
        nodeBegin->next = nodeEnd;
        nodeEnd->prev = nodeBegin;
        return Iterator(nodeBegin);
      };

      void clear();
      void splice(Iterator destPos, List& src, Iterator srcPos);
      void splice(Iterator destPos, List& src, Iterator rangeBegin, Iterator rangeEnd);
      void remove(const T&) {};
      void unique();
      bool operator==(const List&);
      bool operator!=(const List&);
      bool operator<(const List&);
  };
}
