#include "List.hpp"
#include <iostream>
#include <list>
#include <assert.h>
#include <typeinfo>
#include <stdarg.h>
#include <stdio.h>

using namespace cs540;
using namespace std;



#define check(expr) \
    ((expr) ? 0 : fprintf(stderr, "Check failed at line %d in file %s.\n", __LINE__, __FILE__))



#define check_list(expr) \
    ((check_list_helper expr) ? 0 : fprintf(stderr, "Check list failed at line %d in file %s.\n", __LINE__, __FILE__))

// Assume that the sequence of numbers is terminated with a -1.
template <typename T>
bool
check_list_helper(const List<T> &l, int n1, ...) {

    va_list ap;
    va_start(ap, n1);

    int n = n1;
    typename List<T>::ConstIterator it = l.begin();

    // Iterate through the list and the sequence of numbers.
    while (n != -1 && it != l.end()) {
        if (!(*it == T(n))) {
            break;
        }
        ++it;
        n = va_arg(ap, int);
    }

    va_end(ap);

    // The list is only equal to the sequence if we reached the end of both.
    return n == -1 && it == l.end();
}

template <typename T>
ostream &
operator<<(ostream &os, const List<T> &l) {
    os << "[ ";
    for (typename List<T>::ConstIterator it = l.begin(); it != l.end(); ++it) {
        os << (it != l.begin() ? ", " : "") << *it;
    }
    os << " ]";
    return os;
}

// Test routine for multiple iterators.
template <typename T> void traverse(List<T> &l, int level);
// Test routine for multiple lists.
template <typename T> void traverse2(int level);



class MyClass {

        friend std::ostream &operator<<(std::ostream &os, const MyClass &o) {
            os << o.val;
            return os;
        }
        friend inline bool operator==(const MyClass &o1, const MyClass &o2) {
            return o1.val == o2.val;
        }
        friend inline bool operator<(const MyClass &o1, const MyClass &o2) {
            return o1.val < o2.val;
        }

        friend int main();
        friend bool check_list_helper<>(const List<MyClass> &, int n1, ...);
        friend void traverse<MyClass>(List<MyClass> &l, int level);
        friend void traverse2<MyClass>(int level);

    private:

        // Disallow this.
        MyClass();
        // You are not allowed to use the constructor
        // below inside your List class.
        MyClass(int v) : val(v) {}
        // Below is to help test your List implementation.
        // You can use it in your own debugging code, but you must not use it
        // in your actual implementation, because it may not be present
        // in the MyClass that we use to test your List implemenation.
        bool is_const() const { return true; }
        bool is_const() { return false; }


        int val;
};

int
main() {

    // Test default ctor.
    {
        List<MyClass> l;
        check(l.size() == 0);
    }

    // Test copy constructor.
    {
        List<MyClass> l1;
        l1.push_back(1);
        l1.push_back(2);

        List<MyClass> l2(l1);

        check(l1 == l2);

        l2.push_back(3);
        check(l1 != l2);
    }

    // Test assignment operator.
    {
        List<MyClass> l1;
        l1.push_back(1);
        l1.push_back(2);

        List<MyClass> l2;

        l2 = l1;
        check(l2 == l1);

        l2 = l2;
        check(l2 == l2);

        // Check return value is non-const reference.
        List<MyClass> l3;
        l3.push_back(3);
        l3.push_back(3);

        List<MyClass> l4;
        l4.push_back(4);
        l4.push_back(4);

        (l3 = l1) = l4;
        check(l3 == l4);
        check(!(l3 == l1));
    }

    // Test size().
    {
        List<MyClass> l;
        check(l.size() == 0);

        l.push_back(1);
        check(l.size() == 1);

        l.push_back(2);
        check(l.size() == 2);

        l.clear();
        check(l.size() == 0);

        // Test that it is const.
        const List<MyClass> &const_ref(l);
        check(const_ref.size() == 0);
    }

    // Check begin() and end() types.
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);

        check(typeid(l.begin()) == typeid(List<MyClass>::Iterator));
        check(typeid(l.end()) == typeid(List<MyClass>::Iterator));

        const List<MyClass> &const_ref(l);
        check(typeid(const_ref.begin()) == typeid(List<MyClass>::ConstIterator));
        check(typeid(const_ref.end()) == typeid(List<MyClass>::ConstIterator));

        check(typeid(l.rbegin()) == typeid(List<MyClass>::ReverseIterator));
        check(typeid(l.rend()) == typeid(List<MyClass>::ReverseIterator));
    }

    // Check element access.
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);
        List<MyClass> cmp;
        cmp.push_back(3);
        cmp.push_back(5);

        l.front() = MyClass(3);
        check(l.front() == MyClass(3));
        l.back() = MyClass(5);
        check(l.back() == MyClass(5));
        check(l.size() == 2);
        check(l == cmp);

        // Check const versions.
        const List<MyClass> &clr(l);
        check(clr.front().is_const());
        check(clr.back().is_const());
    }

    // Check push_front(), push_back(), pop_front(), and pop_back().
    {
        List<MyClass> l;

        // Check push_front() and push_back();
        l.push_front(1);
        l.push_back(2);
        l.push_back(3);

        check(l.front() == MyClass(1));
        check(l.back() == MyClass(3));
        check(l.size() == 3);

        // Check pop_front();
        List<MyClass> l2(l);
        l2.pop_front();
        check(l2.size() == 2);
        check(l2.front() == MyClass(2));
        check(l2.back() == MyClass(3));

        // Check pop_back();
        List<MyClass> l3(l);
        l3.pop_back();
        check(l3.size() == 2);
        check(l3.front() == MyClass(1));
        check(l3.back() == MyClass(2));
    }

    // Check insert().
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);

        List<MyClass> l2(l);
        List<MyClass>::Iterator it = l2.begin();
        ++it; ++it; // Now points to the 3rd element.
        List<MyClass>::Iterator new_it = l2.insert(it, MyClass(25));

        check_list((l2, 1, 2, 25, 3, 4, -1));

        // Check insert range.
        List<MyClass> l3;
        l3.push_back(21);
        l3.push_back(22);
        l3.push_back(23);
        // Check return value of insert().
        l2.insert(new_it, l3.begin(), l3.end());

        cout << l2 << endl;

        check_list((l2, 1, 2, 21, 22, 23, 25, 3, 4, -1));
        check_list((l3, 21, 22, 23, -1));
    }

    // Check erase.
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);

        List<MyClass>::Iterator it = l.erase(--l.end());
        check_list((l, 1, 2, 3, -1));
        check(it == l.end());

        l.push_back(4);
        // Erase first element.
        it = l.erase(l.begin(), ++l.begin());
        check(*it == MyClass(2));
        check_list((l, 2, 3, 4, -1));
        // Erase range, last element.
        it = l.erase(--l.end(), l.end());
        check_list((l, 2, 3, -1));
        check(it == l.end());
    }

    // Check clear().
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        check(l.size() == 3);
        l.clear();
        check(l.size() == 0);
        l.push_back(4);
        l.push_back(5);
        check_list((l, 4, 5, -1));
    }

    // Check splice().
    {
        List<MyClass> src;
        src.push_back(1);
        src.push_back(2);
        src.push_back(3);
        src.push_back(4);
        src.push_back(5);
        src.push_back(6);
        src.push_back(7);
        src.push_back(8);
        src.push_back(9);
        src.push_back(10);

        List<MyClass> dst;
        dst.splice(dst.end(), src, src.begin());
        check_list((dst, 1, -1));
        check_list((src, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1));

        dst.splice(dst.begin(), src, --src.end(), src.end());
        check_list((dst, 10, 1, -1));
        check_list((src, 2, 3, 4, 5, 6, 7, 8, 9, -1));

        List<MyClass>::Iterator it = src.begin();
        ++it;
        ++it;
        dst.splice(++dst.begin(), src, src.begin(), it);
        check_list((dst, 10, 2, 3, 1, -1));
        check_list((src, 4, 5, 6, 7, 8, 9, -1));

        dst.splice(dst.end(), src, src.begin(), src.end());
        check_list((dst, 10, 2, 3, 1, 4, 5, 6, 7, 8, 9, -1));
        check_list((src, -1));
    }

    // Check remove().
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);
        l.push_back(6);
        l.push_back(6);

        l.remove(1);
        check_list((l, 2, 3, 4, 5, 6, 6, -1));
        l.remove(6);
        check_list((l, 2, 3, 4, 5, -1));
        l.remove(4);
        check_list((l, 2, 3, 5, -1));
        l.remove(6);
        check_list((l, 2, 3, 5, -1));

        // Check empty list.
        l.clear();
        l.remove(3);
    }

    // Check unique().
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(1);
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(1);
        l.push_back(1);
        l.push_back(4);
        l.push_back(4);
        l.push_back(4);

        l.unique();
        check_list((l, 1, 2, 3, 1, 4, -1));

        // Check empty list.
        l.clear();
        l.unique();
    }

    // Check comparison
    {
        List<MyClass> l1, l2;
        check(l1 == l2);
        check(!(l1 < l2));

        l1.push_back(1);
        check(!(l1 == l2));
        check(l2 < l1);

        l2.push_back(2);
        check(l1 < l2);

        l2.clear();
        l2.push_back(1);

        check(l1 == l2);
        check(!(l1 < l2));

        l2.push_back(1);
        check(!(l1 == l2));
        check(l1 < l2);
    }

    // Check Iterator
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);

        List<MyClass>::Iterator it1 = l.begin();
        List<MyClass>::Iterator it2 = it1;
        check(it2 == it1++);
        check(++it2 == it1);
        check(it1-- == it2);
        check(it1 == l.begin());
        check(--it2 == l.begin());

        it1 = l.end();
        check(*--it1 == MyClass(5));
        *it1 = MyClass(6);
        check(++it1 == l.end());
        check(*--it1 == MyClass(6));

        check(!(*it1).is_const());
        check(!it1->is_const());
    }

    // Check ConstIterator
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);

        List<MyClass>::ConstIterator it1 = l.begin();
        List<MyClass>::ConstIterator it2 = it1;
        check(it2 == it1++);
        check(++it2 == it1);
        check(it1-- == it2);
        check(it1 == l.begin());
        check(--it2 == l.begin());

        it1 = l.end();
        check(*--it1 == MyClass(5));
        check(++it1 == l.end());
        check(*--it1 == MyClass(5));

        check((*it1).is_const());
        check(it1->is_const());
    }

    // Check ReverseIterator
    {
        List<MyClass> l;
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);

        List<MyClass>::ReverseIterator it1 = l.rbegin();
        List<MyClass>::ReverseIterator it2 = it1;
        check(it2 == it1++);
        check(++it2 == it1);
        check(it1-- == it2);
        check(it1 == l.rbegin());
        check(--it2 == l.rbegin());

        it1 = l.rend();
        check(*--it1 == MyClass(1));
        *it1 = MyClass(6);
        check(++it1 == l.rend());
        check(*--it1 == MyClass(6));

        check(!(*it1).is_const());
        check(!it1->is_const());
    }

    // Various.
    {
        List<MyClass> l;

        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_front(0);

        List<MyClass> l2(l);
        assert(l2 == l);

        l.erase(l.begin(), l.end());
        assert(l.size() == 0);
        List<MyClass> empty;
        assert(l == empty);

        cout << "l2:" << endl;
        for (List<MyClass>::Iterator it = l2.begin(); it != l2.end(); ++it) {
            cout << *it << endl;
        }

        cout << "reversed l2:" << endl;
        for (List<MyClass>::ReverseIterator it = l2.rbegin(); it != l2.rend(); ++it) {
            cout << *it << endl;
        }

        List<MyClass> l3;

        l3.push_back(1);
        l3.push_back(2);
        l3.push_back(3);
        l3.push_back(4);

        l2.splice(++l2.begin(), l3, ++l3.begin(), --l3.end());

        cout << "l2:" << endl;
        for (List<MyClass>::Iterator it = l2.begin(); it != l2.end(); ++it) {
            cout << *it << endl;
        }

        cout << "l3:" << endl;
        for (List<MyClass>::Iterator it = l3.begin(); it != l3.end(); ++it) {
            cout << *it << endl;
        }
    }

    // Check no element.
    {
        List<MyClass> l1, l2;
        assert(l1 == l2);

        l1.push_back(1);
        assert(l1 != l2);
        assert(l2 != l1);

        l2.push_back(1);
        assert(l1 == l2);
    }

    // Test multiple iterators.
    {
        List<MyClass> l;

        l.push_back(1);
        l.push_back(2);
        l.push_back(3);

        traverse(l, 3);
    }

    // Test multiple lists.
    traverse2<MyClass>(3);
}

template <typename T>
void
traverse(List<T> &l, int level) {
    for (typename List<T>::Iterator it = l.begin(); it != l.end(); ++it) {
        cout << *it << endl;
        if (level != 0) {
            traverse(l, level - 1);
        }
    }
}

template <typename T>
void
traverse2(int level) {

    List<T> l;

    /*
    struct Local {
        static Animal *animal(int id) {
            char name[30];
            sprintf(name, "Spot%d", id);
            return (Animal *) Dog_new(name, id);
        }
    };
    */

    l.push_back(4*level + 1);
    l.push_back(4*level + 2);
    l.push_back(4*level + 3);

    for (typename List<T>::Iterator it = l.begin(); it != l.end(); ++it) {
        cout << *it << endl;
        if (level != 0) {
            traverse2<T>(level - 1);
        }
    }

    /*
    for (List<T>::Iterator it = l.begin(); it != l.end()); ++it) {
        it.deref(&it)->delet(it.deref(&it));
    }
    */
}
