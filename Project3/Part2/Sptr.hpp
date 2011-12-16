namespace cs540 {
  template <typename T>
  class Sptr {
    private:
      class SharedPointer {
        private:
          int refCount;

        public:
          SharedPointer(T& o) : refCount(0), object(o) {}
          void increment() { ++refCount; }
          void decrement() { if(--refCount == 0) delete object; }

          T* object;
      };

    public:
      SharedPointer* sharedPtr;

      Sptr();

      template <typename U>
      Sptr(U*);

      Sptr(const Sptr& s) : sharedPtr(s.sharedPtr) {
        sharedPtr->increment();
      };

      template <typename U>
      Sptr(const Sptr<U>& s) : sharedPtr(static_pointer_cast<Sptr<T>>(s).sharedPtr) {
        sharedPtr->increment();
      }

      Sptr& operator=(const Sptr& s) {
        if(!(*this == s)) {
          sharedPtr->decrement();
          sharedPtr = s.sharedPtr;
        }
        sharedPtr->increment();
        return *this;
      }

      template <typename U>
      Sptr<T>& operator=(const Sptr<U>& s) {
        s = static_pointer_cast<Sptr<T>>(s);
        sharedPtr->decrement();
        sharedPtr = s.sharedPtr;
        sharedPtr->increment();
        return *this;
      }

      void reset();

      T& operator*() const { return *(sharedPtr->object); }
      T* operator->() const { return sharedPtr->object; }

      T* get() const { return sharedPtr->object; }

      operator unspecified_bool_type() const {
        return false; //FIXME
      }
  };

  template <typename T1, typename T2>
  bool operator==(const Sptr<T1>&, const Sptr<T2>&);

  template <typename T, typename U>
  Sptr<T> static_pointer_cast(const Sptr<U>& s) {
    s.sharedPtr->object static_cast<T>(s.)
  }

  template <typename T, typename U>
  Sptr<T> dynamic_pointer_cast(const Sptr<U>&);
}
