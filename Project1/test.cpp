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
     * Test Part 1, Person hierarchy.
     */

    Person *p1 = 0;
    {
        /*
         * Create an Under object.
         */

        printf("---- Under\n");

        char *n = strdup("Jane");
        char *major = strdup("CS");
        p1 = (Person *) Under_new(n, 'F', major, 4);
        free(n);
        free(major);

        // Prints:
        // Name: <name>
        // Gender: <gender>
        Person_print(p1);
        // Note that Grad and Under print the same thing for work,
        // and so can share the implementation.
        p1->work(p1); // Prints "<name> studies <major>."

        Student *s = Person_downcast_Student(p1); // Must return null if not a Student.
        Student_print(s); // Prints "Major: <major>"
        // Assume year 4 means one more year to go.
        s->graduate(s); // Prints "<name> graduates in <N> years and finds a job in <major> or goes to grad school."

        Under *u = Person_downcast_Under(p1); // Must return null if not an Under.
        assert(Student_downcast_Under(s) == u);
        Under_print(u); // Prints "Year: <year>"

        // Check that upcast still works right.
        assert((Person *) u == p1);

        // Check that other downcasts fail.
        assert(Person_downcast_Grad(p1) == 0);
        assert(Person_downcast_Professor(p1) == 0);
        assert(Student_downcast_Grad(s) == 0);
    }

    Person *p2 = 0;
    {
        /*
         * Create an Grad object.
         */

        printf("---- Grad\n");

        char *n = strdup("John");
        char *major = strdup("Biology");
        char *degree = strdup("PhD");
        p2 = (Person *) Grad_new(n, 'M', major, degree);
        free(n);
        free(major);
        free(degree);

        Person_print(p2);
        p2->work(p2); // Same as Under.

        Student *s = Person_downcast_Student(p2);
        Student_print(s);
        s->graduate(s); // Prints "<name> graduates with a <degree> and finds a job in <major>."

        Grad *g = Person_downcast_Grad(p2);
        assert(Student_downcast_Grad(s) == g);
        Grad_print(g); // Prints "Degree: <degree>"

        // Check that other downcasts fail.
        assert(Person_downcast_Under(p2) == 0);
        assert(Person_downcast_Professor(p2) == 0);
        assert(Student_downcast_Under(s) == 0);
    }

    Person *p3 = 0;
    {
        /*
         * Create an Professor object.
         */

        printf("---- Professor\n");

        char *name = strdup("Mary");
        char *office = strdup("T-10");
        p3 = (Person *) Professor_new(name, 'F', office);
        free(name);
        free(office);

        Person_print(p3);
        p3->work(p3); // Prints "<name> teaches."

        Professor *p = Person_downcast_Professor(p3);
        Professor_print(p); // Prints "Office: <office>"
        p->research(p, "computers"); // Must print "<name> does research in <topic>."
        p->research(p, "frogs");

        // Check that other downcasts fail.
        assert(Person_downcast_Student(p3) == 0);
        assert(Person_downcast_Under(p3) == 0);
        assert(Person_downcast_Grad(p3) == 0);
    }

    Person *p4 = (Person *) Under_new("Dave", 'M', "Chemistry", 2);
}

