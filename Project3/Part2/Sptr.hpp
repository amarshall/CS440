#include <pthread.h>

namespace cs540 {
  class Proxy {
    private:
      int refCount;
      pthread_mutex_t lock;

    public:
      Proxy() : refCount(0) { pthread_mutex_init(&lock, 0); }
      virtual ~Proxy() {}

      int decrement() {
        int r;
        pthread_mutex_lock(&lock);
        if(refCount > 0) {
          r = --refCount;
        } else {
          r = refCount;
        }
        pthread_mutex_unlock(&lock);
        return r;
      }

      int increment() {
        pthread_mutex_lock(&lock);
        int r = ++refCount;
        pthread_mutex_unlock(&lock);
        return r;
      }
  };

  template <typename U>
  class Proxy_t : public Proxy {
    private:
      U* object;

    public:
      Proxy_t(U* o) : object(o) {}
      virtual ~Proxy_t() { delete object; }
  };

  template <typename T>
  class Sptr {
    typedef void (Sptr<T>::*unspecified_bool_type)() const;
    void this_type_does_not_support_comparisons() const {}

    template <typename A> friend class Sptr;

    public:
      T* object;

    private:
      Proxy* proxy;

    public:
      Sptr() : object(0), proxy(0) {}

      template <typename U>
      Sptr(U* o) : object(o), proxy(new Proxy_t<U>(o)) {}

      Sptr(const Sptr& s) : object(s.object), proxy(s.proxy) {
        proxy->increment();
      };

      template <typename U>
      Sptr(const Sptr<U>& s) : object(static_cast<T*>(s.object)), proxy(s.proxy) {
        proxy->increment();
      }

      Sptr& operator=(const Sptr& s) {
        if(!(*this == s)) {
          if(object != 0 && proxy->decrement() == 0) delete proxy;
          object = s.object;
          proxy = s.proxy;
        }
        proxy->increment();
        return *this;
      }

      template <typename U>
      Sptr<T>& operator=(const Sptr<U>& s) {
        if(object != 0 && proxy->decrement() == 0) delete proxy;
        object = static_cast<T*>(s.object);
        proxy = s.proxy;
        proxy->increment();
        return *this;
      }

      void reset() {
        if(object != 0 && proxy->decrement() == 0) delete proxy;
        object = 0;
        proxy = 0;
      }

      T& operator*() const { return *object; }
      T* operator->() const { return object; }

      T* get() const { return object; }

      operator unspecified_bool_type() const {
        return object != 0 ? &Sptr<T>::this_type_does_not_support_comparisons : 0;
      }
  };

  template <typename T1, typename T2>
  bool operator==(const Sptr<T1>& one, const Sptr<T2>& two) {
    return one.object == two.object;
  }

  template <typename T, typename U>
  Sptr<T> static_pointer_cast(const Sptr<U>& s) {
    return Sptr<T>(static_cast<T*>(s.object));
  }

  template <typename T, typename U>
  Sptr<T> dynamic_pointer_cast(const Sptr<U>& s) {
    return Sptr<T>(dynamic_cast<T*>(s.object));
  }
}
