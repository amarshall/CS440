#include <stdlib.h>

namespace cs540 {
  template <typename T>
  class List {
    private:
      class Link {
        public:
          Link() {}
          Link* prev;
          Link* next;
      };

      class Node : public Link {
        public:
          Node(const T& o) : object(o) {}
          T object;
      };

      Link sentinel;
      size_t _size;

    public:
      class Iterator {
        friend class List;
        public:
          virtual Iterator& operator++() { link = link->next; return *this; }
          virtual Iterator operator++(int) { link = link->next; return *this; }
          virtual Iterator& operator--() { link = link->prev; return *this; }
          virtual Iterator operator--(int) { link = link->prev; return *this; }
          T& operator*() const { return static_cast<Node*>(link)->object; };
          T* operator->() const { return &(static_cast<Node*>(link)->object); };
          virtual bool operator==(const Iterator& it) { return link == it.link; }
          virtual bool operator!=(const Iterator& it) { return link != it.link; }

        protected:
          Link* link;

        private:
          Iterator(Link* n) : link(n) {};
          Iterator(const Link* n) : link(n) {};
      };

      class ConstIterator : public Iterator {
        friend class List;
        public:
          ConstIterator(const Iterator& o) : Iterator(o.link) {}
          const T& operator*() const { return static_cast<Node*>(this->link)->object; };
          const T* operator->() const { return &(static_cast<Node*>(this->link)->object); };

        private:
          ConstIterator(Link* n) : Iterator(n) {}
          ConstIterator(const Link* n) : Iterator(n) {}
      };

      class ReverseIterator : public Iterator {
        friend class List;
        public:
          T& operator*() const { return static_cast<Node*>(this->link)->object; };
          T* operator->() const { return &(static_cast<Node*>(this->link)->object); };

        private:
          ReverseIterator(Link* n) : Iterator(n) {}
      };

      List() : _size(0) {
        sentinel.prev = &sentinel;
        sentinel.next = &sentinel;
      }

      List(const List& list) : _size(0) {
        sentinel.prev = &sentinel;
        sentinel.next = &sentinel;
        for(ConstIterator it = list.begin(); it != list.end(); ++it) {
          push_back(*it);
        }
      }

      List& operator=(const List& list) {
        if(this != &list) {
          clear();
          for(ConstIterator it = list.begin(); it != list.end(); ++it) {
            push_back(*it);
          }
        }
        return *this;
      }

      size_t size() const { return _size; }

      Iterator begin() { return Iterator(sentinel.next); }
      Iterator end() { return Iterator(&sentinel); }

      ConstIterator begin() const { return ConstIterator(sentinel.next); }
      ConstIterator end() const { return ConstIterator(const_cast<Link*>(&sentinel)); }

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

      template <typename IT_T> void insert(Iterator pos, IT_T rangeBegin, IT_T rangeEnd) {
        for(IT_T it = rangeBegin; it != rangeEnd; ++it) insert(pos, *it);
      }
      Iterator insert(Iterator pos, const T& obj) {
        Link* n = new Node(obj);
        Link* before = pos.link->prev;
        Link* after = pos.link;
        n->prev = before;
        n->next = after;
        before->next = n;
        after->prev = n;
        ++_size;
        return --pos;
      }

      void clear() { erase(begin(), end()); }
      Iterator erase(Iterator rangeBegin, Iterator rangeEnd) {
        for(Iterator it = rangeBegin; it != rangeEnd;) it = erase(it);
        return rangeEnd;
      };
      Iterator erase(Iterator pos) {
        Link* l = pos.link;
        Link* before = l->prev;
        Link* after = l->next;

        before->next = after;
        after->prev = before;
        delete l;
        --_size;

        return Iterator(after);
      };

      void splice(Iterator destPos, List& src, Iterator srcPos) { splice(destPos, src, srcPos, ++srcPos); }
      void splice(Iterator destPos, List& src, Iterator rangeBegin, Iterator rangeEnd) {
        insert(destPos, rangeBegin, rangeEnd);
        src.erase(rangeBegin, rangeEnd);
      };

      void remove(const T& obj) {
        for(Iterator it = begin(); it != end(); ++it) {
          if(*it == obj) it = --erase(it);
        }
      };

      void unique() {
        for(Iterator it = begin(); it != end();) {
          if(*it == *(it++)) it = erase(it);
        }
      }

      bool operator==(const List& list) {
        if(size() == list.size()) {
          ConstIterator one = begin();
          ConstIterator two = list.begin();
          for(; one != end() && two != list.end(); ++one, ++two) {
            if(*one != *two) return false;
          }
          return true;
        } else {
          return false;
        }
      }
      bool operator!=(const List& list) { return !(*this == list); }
      bool operator<(const List& list) {
        bool lessThan = false;
        ConstIterator one = begin();
        ConstIterator two = list.begin();
        for(; one != end() && two != list.end(); ++one, ++two) {
          // No MyClass::operator< means logical :(
          if(*two < *one) return false;
          if(*one != *two) lessThan = true;
        }
        return lessThan || two != list.end();
      }
  };
}
