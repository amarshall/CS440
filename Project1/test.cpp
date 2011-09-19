/*
 * Run with
 *
 *    -i iterations
 *
 * to do a stress test for the given number of iterations.
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <set>
#include <vector>

#include "Person.hpp"
#include "BinarySearchTree.hpp"

/*
 * Person hierarchy print functions.
 * These are not intended to be member functions, but more like
 * non-member helper functions.
 */

void
Person_print(Person *p) {
    printf("Name: %s\n", p->name);
    printf("Gender: %c\n", p->gender);
}

void
Student_print(Student *s) {
    printf("Major: %s\n", s->major);
}

void
Under_print(Under *u) {
    printf("Year: %d\n", u->year);
}

void
Grad_print(Grad *g) {
    printf("Degree: %s\n", g->degree);
}

void
Professor_print(Professor *p) {
    printf("Office: %s\n", p->office);
}

typedef Person *PersonPtr;

/*
 * BinarySearchTree test functions.
 */

// Comparison function, used later.
bool
PersonPtr_less(const PersonPtr &p1, const PersonPtr &p2) {
    return strcmp(p1->name, p2->name) < 0;
}

// This "instantiates" the template.
// Note that there is no semicolon.
// BinarySearchTree_DEFINE(PersonPtr)


bool
MyClass_less(const MyClass &o1, const MyClass &o2) {
    return o1.num < o2.num;
}

// BinarySearchTree_DEFINE(MyClass)

// int BST

bool
int_less(const int &i1, const int &i2) {
    return i1 < i2;
}
// BinarySearchTree_DEFINE(int)

// Stress test BST

// struct Stress {
    // int val;
    // Stress(int _v) : val(_v){}
// };

// bool
// Stress_less(const Stress& o1, const Stress& o2) {
    // return o1.val < o2.val;
// }
// BinarySearchTree_DEFINE(Stress)


/*
 * Additional test functions for BST.
 */

// void traverse(BinarySearchTree_PersonPtr &l, int level);
void traverse2(int level);
// void check(BinarySearchTree_Stress *bst, std::set<int> &mirror);

// Below is a helper function for the testing only.  It not necessary for the
// actual container.
// bool
// Stress_Iterator_less(const BinarySearchTree_Stress_Iterator& lhs, const BinarySearchTree_Stress_Iterator& rhs) {
    // BinarySearchTree_Stress_Iterator it1, it2;
    // it1 = lhs;
    // it2 = rhs;
    // Stress s1 = it1.deref(&it1);
    // Stress s2 = it2.deref(&it2);
    // return s1.val < s2.val;
// }

/*
 * Main.
 */

int
main(int argc, char *argv[]) {

    int c;
    int iterations = 0;
    while ((c = getopt(argc, argv, "i:")) != EOF) {
        switch (c) {
            case 'i':
                iterations = atoi(optarg);
                break;
            case '?':
                fprintf(stderr, "Unrecog.\n");
                exit(1);
        }
    }

    srand48(1234);


    /**************************************************************************
     * Test Part 2, BinarySearchTree template.
     */

    /*
     * Test with Person.
     */

    // {
        // // This creates a BST of pointers to Person objects.  It corresponds to
        // // what in real C++ might be std::set<Person *>.  Note that it is not a
        // // BST of Person objects, but rather of _pointers_ to Person
        // // objects.
        // BinarySearchTree_PersonPtr *bst = BinarySearchTree_PersonPtr_new(PersonPtr_less);

        // // Should print "---- BinarySearchTree_PersonPtr, 27".
        // printf("---- %s, %d\n", bst->type, (int) sizeof(bst->type));

        // // Insert people into the BST.
        // bst->insert(bst, p1);
        // bst->insert(bst, p2);
        // bst->insert(bst, p3);
        // bst->insert(bst, p4);

        // // Check iterator equality.
        // {
            // // Returns an iterator pointing to the first element.
            // BinarySearchTree_PersonPtr_Iterator it1 = bst->begin(bst);
            // // Returns an iterator pointing to one PAST the last element.  This
            // // iterator is obviously conceptual only.  It cannot be dereferenced.
            // BinarySearchTree_PersonPtr_Iterator it2 = bst->end(bst);

            // // inc() advances the iterator forward.  dec() decrements the iterator
            // // so it points to the preceding element.
            // it1.inc(&it1); // Second node now.
            // it1.inc(&it1); // Third node now.
            // it2.dec(&it2); // Fourth node now.
            // it2.dec(&it2); // Third node now.
            // assert(BinarySearchTree_PersonPtr_Iterator_equal(it1, it2));
            // it2.dec(&it2); // Second node now.
            // it2.dec(&it2); // First node now.
            // assert(BinarySearchTree_PersonPtr_Iterator_equal(bst->begin(bst), it2));
        // }

        // // Check insert return value.
        // {
            // printf("---- Test insert() return.\n");
            // // Insert returns an interator.  The value is end(), if the element is
            // // already in the container.  Otherwise, the iterator points to the
            // // element, and can be used to erase the element.
            // BinarySearchTree_PersonPtr_Iterator it = bst->insert(bst, p1);
            // // Already in, so must return equal to end().
            // assert(BinarySearchTree_PersonPtr_Iterator_equal(it, bst->end(bst)));
            // // Now insert one that is new.
            // Person *pp = (Person *) Professor_new("Larry", 'M', "F9");
            // it = bst->insert(bst, pp);
            // Person_print(it.deref(&it));
            // bst->erase(bst, it);
            // pp->delet(pp);
        // }

        // // Print the whole thing now, to verify ordering.
        // printf("---- Before erasures.\n");

        // // Iterate through the whole BST, and call work() on each
        // // Person.  deref() returns what the iterator was pointing to.
        // for (BinarySearchTree_PersonPtr_Iterator it = bst->begin(bst);
         // !BinarySearchTree_PersonPtr_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            // Person *p = it.deref(&it);
            // p->work(p);
        // }

        // // Test multiple traversals of the same BST.
        // printf("---- Multiple traversals\n");
        // traverse(*bst, 3);

        // // Test multiple BST at the same time.
        // printf("---- Multiple BST\n");
        // traverse2(4);

        /*
         * Test some erasures.
         */

        // // Erase first element.
        // bst->erase(bst, bst->begin(bst));
        // BinarySearchTree_PersonPtr_Iterator it = bst->end(bst);
        // it.dec(&it); // it now points to last element.
        // it.dec(&it); // it now points to penultimate element.
        // bst->erase(bst, it);

        // printf("---- After erasures.\n");

        // // Iterate through the whole BST, and call work() on each
        // // Person.
        // for (BinarySearchTree_PersonPtr_Iterator it = bst->begin(bst);
         // !BinarySearchTree_PersonPtr_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            // Person *p = it.deref(&it);
            // p->work(p);
        // }

        // // Test iterator validity.
        // {
            // // Iterators must be valid even when other things are
            // // inserted.
            // printf("---- Test iterator non-invalidation\n");

            // Person *pp = (Person *) Professor_new("Zeke", 'M', "F9");
            // // Will be at the end.
            // BinarySearchTree_PersonPtr_Iterator it = bst->insert(bst, pp);
            // // Delete first, iterator should still be valid.
            // BinarySearchTree_PersonPtr_Iterator b = bst->begin(bst);
            // Person *tmp = b.deref(&b); // Save, so we can reinsert.
            // bst->erase(bst, bst->begin(bst)); // Erase it.
            // Person_print(it.deref(&it)); // This should still be valid.
            // bst->insert(bst, tmp); // Reinsert.
            // bst->erase(bst, it); // Erase.
            // pp->delet(pp); // Cleanup.
        // }

        // // Must not delete the actual Person objects.  Note that we cannot use
        // // 'delete', because it is a reserved word (keyword).
        // bst->delet(bst);

        // // Note that these functions must cleanup after the derived object.  For
        // // example, if p1 is a Under, delet() must cleanup after Under.  These are
        // // what we call "virtual destructors", which we will talk about more later.
        // p1->delet(p1);
        // p2->delet(p2);
        // p3->delet(p3);
        // p4->delet(p4);
    // }

    /*
     * Test BST with MyClass.
     */

    {
        MyClass m1, m2, m3, m4, m5;
        m1.num = 0;
        m2.num = 3;
        m3.num = 1;
        m4.num = 2;
        m5.num = -999;
        BinarySearchTree_MyClass* bst = BinarySearchTree_MyClass_new(MyClass_less);

        // Should print "---- BinarySearchTree_MyClass, 25".
        printf("---- %s, %d\n", bst->type, (int) sizeof(bst->type));

        BinarySearchTree_MyClass_Iterator it;
        // Empty container, should print nothing.
        for (it = bst->begin(bst);
         !BinarySearchTree_MyClass_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        bst->insert(bst, m1);
        bst->insert(bst, m2);
        bst->insert(bst, m3);
        bst->insert(bst, m4);

        // Should print 0.0 1.0 2.0 3.0
        for (it = bst->begin(bst);
         !BinarySearchTree_MyClass_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Check return value of insert.
        {
            MyClass dupe;
            dupe.num = m1.num;

            // Already in, so must return equal to end().
            it = bst->insert(bst, dupe);
            assert(BinarySearchTree_MyClass_Iterator_equal(it, bst->end(bst)));
        }

        // Erase the first element.
        bst->erase(bst, bst->begin(bst));
        // Should print "1.0 2.0 3.0".
        for (it = bst->begin(bst);
         !BinarySearchTree_MyClass_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Erase the new first element.
        bst->erase(bst, bst->begin(bst));
        // Should print "2.0 3.0".
        for (it = bst->begin(bst);
         !BinarySearchTree_MyClass_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Erase the element in the end.
        it = bst->end(bst);
        it.dec(&it); // It now points to last element.
        bst->erase(bst, it);
        // Should print "2.0".
        for (it = bst->begin(bst);
         !BinarySearchTree_MyClass_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        // Erase the last element.
        bst->erase(bst, bst->begin(bst));
        // Should print nothing.
        for (it = bst->begin(bst);
                !BinarySearchTree_MyClass_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            MyClass m = it.deref(&it);
            printf("%3.1f ", m.num);
        }
        printf("\n");

        bst->delet(bst);
    }

    /*
     * Test BST with plain int.
     */

    // {
        // BinarySearchTree_int* bst = BinarySearchTree_int_new(int_less);
        // // Should print "---- BinarySearchTree_int, 21".
        // printf("---- %s, %d\n", bst->type, (int) sizeof(bst->type));

        // BinarySearchTree_int_Iterator it;
        // // Empty container, should print nothing.
        // for (it = bst->begin(bst);
         // !BinarySearchTree_int_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            // printf("%d ", it.deref(&it));
        // }
        // printf("\n");

        // bst->insert(bst, 4);
        // bst->insert(bst, 3);
        // bst->insert(bst, 0);
        // bst->insert(bst, 2);
        // bst->insert(bst, 1);

        // // Should print "0 1 2 3 4".
        // for (it = bst->begin(bst);
         // !BinarySearchTree_int_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            // printf("%d ", it.deref(&it));
        // }
        // printf("\n");

        // // Insert dupes.
        // bst->insert(bst, 4);
        // bst->insert(bst, 3);
        // bst->insert(bst, 0);
        // bst->insert(bst, 2);
        // bst->insert(bst, 1);
        // // Should print "0 1 2 3 4".
        // for (it = bst->begin(bst);
         // !BinarySearchTree_int_Iterator_equal(it, bst->end(bst)); it.inc(&it)) {
            // printf("%d ", it.deref(&it));
        // }
        // printf("\n");

        // // Erase the first element.
        // bst->erase(bst, bst->begin(bst));

        // // Erase the new first element.
        // bst->erase(bst, bst->begin(bst));

        // // Erase the element in the end.
        // it = bst->end(bst);
        // it.dec(&it); // It now points to last element.
        // bst->erase(bst, it);
        // // Should print "2 3".
        // for (it = bst->begin(bst); !BinarySearchTree_int_Iterator_equal(it, bst->end(bst)); it.inc(&it))
            // printf("%d ", it.deref(&it));
        // printf("\n");

        // // Erase all elements.
        // bst->erase(bst, bst->begin(bst));
        // bst->erase(bst, bst->begin(bst));
        // // Should print nothing.
        // for (it = bst->begin(bst); !BinarySearchTree_int_Iterator_equal(it, bst->end(bst)); it.inc(&it))
            // printf("%d ", it.deref(&it));
        // printf("\n");

        // bst->delet(bst);
    // }

    /*
     * Stress test BST.
     */

    // if (iterations > 0) {
        // BinarySearchTree_Stress* bst = BinarySearchTree_Stress_new(Stress_less);
        // typedef std::set<int> mirror_t;
        // mirror_t mirror;
        // typedef std::set<BinarySearchTree_Stress_Iterator, bool(*)(const BinarySearchTree_Stress_Iterator& lhs, const BinarySearchTree_Stress_Iterator& rhs)> iters_t;
        // iters_t iters(&Stress_Iterator_less);

        // std::cout << "---- Starting stress test:" << std::endl;

        // const int N = iterations;

        // srand(9757);
        // int n_inserted = 0, n_erased = 0, n_iters_changed = 0, n_empty = 0, n_dupes = 0;
        // double avg_size = 0;

        // for (int i = 0; i < N; ++i) {

            // double op = drand48();

            // // The probability of removal should be slightly higher than the
            // // probability of insertion so that the BST is often empty.
            // if (op < .44) {

                // // Insert an element.  Repeat until no duplicate.
                // do {
                    // int v = rand();
                    // std::pair<mirror_t::iterator, bool> res = mirror.insert(v);
                    // BinarySearchTree_Stress_Iterator it = bst->insert(bst, Stress(v));
                    // if (res.second) {
                        // // If insert into mirror succeeded, insert into BST should also have succeeded.
                        // assert(!BinarySearchTree_Stress_Iterator_equal(it, bst->end(bst)));
                        // // Store the iterator.
                        // iters.insert(it);
                        // break;
                    // }
                    // // If insert into mirror did not succeed, insert into BST
                    // // should also not have succeeded, in which case, we
                    // // generate another value to store.
                    // assert(BinarySearchTree_Stress_Iterator_equal(it, bst->end(bst)));
                    // n_dupes++;
                // } while (true);

                // ++n_inserted;

            // } else if (op < .90) {

                // // Erase an element.
                // if (iters.size() != 0) {

                    // // Pick a random index.
                    // int index = rand()%iters.size();
                    // iters_t::iterator iit = iters.begin();
                    // while(index--) {
                        // ++iit;
                    // }

                    // BinarySearchTree_Stress_Iterator it = *iit;
                    // // The iterator should not be end()
                    // assert(!BinarySearchTree_Stress_Iterator_equal(it, bst->end(bst)));

                    // Stress s = it.deref(&it);
                    // mirror.erase(s.val);
                    // iters.erase(iit);
                    // bst->erase(bst, it);

                    // ++n_erased;
                // }

            // } else {

                // // Increment or decrement an iterator.

                // // Size of containers should be same
                // assert(iters.size() == mirror.size());

                // // If the container is empty, skip
                // if (iters.size() != 0) {

                    // // Pick a random index
                    // int index = rand()%iters.size();
                    // iters_t::iterator iters_it = iters.begin();
                    // while (index--) {
                        // ++iters_it;
                    // }

                    // BinarySearchTree_Stress_Iterator it = *iters_it;
                    // // The iterator should not be end().
                    // assert(!BinarySearchTree_Stress_Iterator_equal(it, bst->end(bst)));

                    // // If it is the begin(), then only increment,
                    // // otherwise, pick either forward or backward.
                    // if (BinarySearchTree_Stress_Iterator_equal(it, bst->begin(bst))) {
                        // it.inc(&it);
                        // ++iters_it;
                    // } else {
                        // if (rand()%2 == 0) {
                            // it.inc(&it);
                            // ++iters_it;
                        // } else {
                            // it.dec(&it);
                            // --iters_it;
                        // }
                    // }
                    // // If we didn't hit the end, replace the resulting iterator
                    // // in the iterator list.
                    // if (!BinarySearchTree_Stress_Iterator_equal(it, bst->end(bst))) {
                        // assert(BinarySearchTree_Stress_Iterator_equal(it, *iters_it));
                        // iters.erase(iters_it);
                        // iters.insert(it);
                    // }
                // }

                // ++n_iters_changed;
            // }

            // avg_size += double(iters.size())/N;

            // if (iters.size() == 0) {
                // ++n_empty;
            // }

            // check(bst, mirror);
        // }

        // std::cout << "inserted: " << n_inserted << " times" << std::endl;
        // std::cout << "erased: " << n_erased << " times" << std::endl;
        // std::cout << "iterators changed: " << n_iters_changed << " times" << std::endl;
        // std::cout << "empty count: " << n_empty << std::endl;
        // std::cout << "avg size: " << avg_size << std::endl;
        // // std::cout << "n dupes: " << n_dupes << std::endl;

        // bst->delet(bst);
    // }
}

// void
// check(BinarySearchTree_Stress *bst, std::set<int> &mirror) {

    // // Check if the reference container and stress container is identical
    // BinarySearchTree_Stress_Iterator it = bst->begin(bst);
    // std::set<int>::iterator mit = mirror.begin();

    // for( ; !BinarySearchTree_Stress_Iterator_equal(it, bst->end(bst)) && mit != mirror.end(); it.inc(&it), ++mit) {
        // Stress e = it.deref(&it);
        // if (e.val != *mit) {
            // fprintf(stderr, "Reference tree and test tree differ.\n");
            // abort();
        // }
    // }

    // if(!BinarySearchTree_Stress_Iterator_equal(it, bst->end(bst)) || mit!=mirror.end()) {
        // fprintf(stderr, "Reference tree and test tree differ.\n");
        // abort();
    // }
// }

// Test single list being traversed by multiple iterators simultaneously.
// void
// traverse(BinarySearchTree_PersonPtr &bst, int level) {
    // for (BinarySearchTree_PersonPtr_Iterator it = bst.begin(&bst); !BinarySearchTree_PersonPtr_Iterator_equal(it, bst.end(&bst)); it.inc(&it)) {
        // Person_print(it.deref(&it));
        // if (level != 0) {
            // traverse(bst, level - 1);
        // }
    // }
// }

// Test multiple lists.
// void
// traverse2(int level) {

    // BinarySearchTree_PersonPtr *bst = BinarySearchTree_PersonPtr_new(PersonPtr_less);

    // struct Local {
        // static Person *person() {
            // char name[30];
            // sprintf(name, "Jane%d", int(10000*drand48()));
            // return (Person *) Professor_new(name, 'F', "T-10");
        // }
    // };

    // for (int i = 0; i < 4; i++) {
        // Person *p = Local::person();
        // BinarySearchTree_PersonPtr_Iterator it = bst->insert(bst, p);
        // // If a duplicate (unlikely but possible), free it, because it
        // // didn't get inserted.
        // if (BinarySearchTree_PersonPtr_Iterator_equal(it, bst->end(bst))) {
            // p->delet(p);
        // }
    // }

    // for (BinarySearchTree_PersonPtr_Iterator it = bst->begin(bst);
     // !BinarySearchTree_PersonPtr_Iterator_equal(it, bst->end(bst));
     // it.inc(&it)) {
        // Person_print(it.deref(&it));
        // if (level != 0) {
            // traverse2(level - 1);
        // }
    // }

    // // Remove from BST before deleting, to avoid having pointers to
    // // deleted Person objects in the BST, which can mess up
    // // some algorithms for incrementing.
    // {
        // std::vector<Person *> del_list;
        // for (BinarySearchTree_PersonPtr_Iterator it = bst->begin(bst);
         // !BinarySearchTree_PersonPtr_Iterator_equal(it, bst->end(bst));
         // it.inc(&it)) {
            // del_list.push_back(it.deref(&it));
        // }

        // bst->delet(bst);

        // for (size_t i = 0; i < del_list.size(); i++) {
            // del_list.at(i)->delet(del_list.at(i));
        // }
    // }
// }
