namespace cs540 {
  class SharedCounter {
    public:
      SharedCounter() : refCount(0) {}
      int refCount;
      int decrement() { if(refCount > 0) { --refCount; } return refCount; }
      int increment() { return ++refCount; }
  };

  template <typename T>
  class Sptr {
    typedef void (Sptr<T>::*unspecified_bool_type)() const;
    void this_type_does_not_support_comparisons() const {}

    template <typename A> friend class Sptr;

    private:
      SharedCounter* counter;

    public:
      T* object;

      Sptr() : counter(new SharedCounter()) {}

      template <typename U>
      Sptr(U* o) : counter(new SharedCounter()), object(static_cast<T*>(o)) {}

      Sptr(const Sptr& s) : counter(s.counter), object(s.object) {
        counter->refCount++;
      };

      template <typename U>
      Sptr(const Sptr<U>& s) {
        object = static_cast<T*>(s.object);
        counter = static_cast<SharedCounter*>(s.counter);
        counter->refCount++;
      }

      Sptr& operator=(const Sptr& s) {
        if(!(*this == s)) {
          if(counter->decrement() == 0) delete object;
          object = s.object;
          counter = const_cast<SharedCounter*>(s.counter);
        }
        counter->refCount++;
        return *this;
      }

      template <typename U>
      Sptr<T>& operator=(const Sptr<U>& s) {
        if(counter->decrement() == 0) delete object;
        object = static_cast<T*>(s.object);
        counter = const_cast<SharedCounter*>(s.counter);
        counter->refCount++;
        return *this;
      }

      void reset() {
        if(counter->decrement() == 0) delete object;
        object = 0;
      }

      T& operator*() const { return *object; }
      T* operator->() const { return object; }

      T* get() const { return object; }

      operator unspecified_bool_type() const {
        return object == 0 ? &Sptr<T>::this_type_does_not_support_comparisons : 0;
      }
  };

  template <typename T1, typename T2>
  bool operator==(const Sptr<T1>&, const Sptr<T2>&);

  template <typename T, typename U>
  Sptr<T> static_pointer_cast(const Sptr<U>& s) {
    return Sptr<T>(static_cast<T*>(s.object));
  }

  template <typename T, typename U>
  Sptr<T> dynamic_pointer_cast(const Sptr<U>& s) {
    return Sptr<T>(dynamic_cast<T*>(s.object));
  }
}
