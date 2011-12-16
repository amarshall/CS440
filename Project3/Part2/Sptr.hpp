namespace cs540 {
  template <typename T>
  class Sptr {
    private:

    public:
      Sptr();
      template <typename U> Sptr(U*);

      Sptr& operator=(const Sptr&);
      template <typename U> Sptr<T>& operator=(const Sptr<U>&);

      void reset();

      T& operator*() const;
      T* operator->() const;

      T* get() const;

      operator unspecified_bool_type() const;
  };

  template <typename T1, typename T2>
  bool operator==(const Sptr<T1>&, const Sptr<T2>&);

  template <typename T, typename U>
  Sptr<T> static_pointer_cast(const Sptr<U>&);

  template <typename T, typename U>
  Sptr<T> dynamic_pointer_case(const Sptr<U>&);
}
