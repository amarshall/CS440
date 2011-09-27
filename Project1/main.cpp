#include "Person.hpp"
#include <iostream>

int main() {
  Under* u = Under_new("John Smith", 'M', "CS", 3);
  Under* u2 = Under_new("John Smith", 'M', "CS", 4);
  Person* p = (Person*)Under_new("John Smith", 'M', "CS", 4);

  printf("%d\n", u->year);
  printf("%d\n", u2->year);
  printf("%s\n", p->name);
  p->work(p);

  return 0;
}
