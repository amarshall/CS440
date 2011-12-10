#include <stdlib.h>

namespace cs540 {
  template <typename T>
  class List {
    public:
      class Iterator {
        public:
          Iterator(const Iterator&);
          Iterator& operator=(const Iterator&);
          Iterator& operator++();
          Iterator& operator--();
          Iterator operator--(int);
          T& operator*() const;
          T* operator->() const;
          virtual bool operator==(const Iterator&);
          virtual bool operator!=(const Iterator&);

        private:
      };

      class ConstIterator : public Iterator {
        public:
          ConstIterator(const ConstIterator&);
          ConstIterator& operator=(const ConstIterator&);
          ConstIterator& operator++();
          ConstIterator& operator--();
          ConstIterator operator--(int);
          T& operator*() const;
          T* operator->() const;

        private:
      };

      class ReverseIterator : public Iterator {
        public:
          ReverseIterator(const ReverseIterator&);
          ReverseIterator& operator=(const ReverseIterator&);
          ReverseIterator& operator++();
          ReverseIterator& operator--();
          ReverseIterator operator--(int);
          T& operator*() const;
          T* operator->() const;

        private:
      };

      List();
      List(const List&);
      List& operator=(const List&);
      size_t size() const;
      Iterator begin();
      Iterator end();
      ConstIterator begin() const;
      ConstIterator end() const;
      ReverseIterator rbegin() const;
      ReverseIterator rend() const;
      T& front();
      const T& front() const;
      T& back();
      const T& back() const;
      void push_front(const T&);
      void push_back(const T&);
      Iterator insert(Iterator pos, const T&);
      template <typename IT_T> void insert(Iterator pos, IT_T rangeBegin, IT_T rangeEnd);
      Iterator erase(Iterator pos);
      Iterator erase(Iterator rangeBegin, Iterator rangeEnd);
      void remove(const T&);
      void unique();
      bool operator==(const List&);
      bool operator<(const List&);

    private:
  };
}
