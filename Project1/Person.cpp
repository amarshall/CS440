#include "Person.hpp"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

Professor* Professor_new(char* name, char gender, char* office) {
  Professor* professor = (Professor*) malloc(sizeof(Professor));
  professor->person.name = strdup(name);
  professor->person.gender = gender;
  professor->office = strdup(office);
  professor->person.work = &work_professor;
  professor->person.type_check = &type_check_professor;
  professor->research = &research;

  return professor;
}

Grad* Grad_new(char* name, char gender, char* major, char* degree) {
  Grad* grad = (Grad*) malloc(sizeof(Grad));
  grad->student.person.name = strdup(name);
  grad->student.person.gender = gender;
  grad->student.major = strdup(major);
  grad->degree = degree;
  grad->student.person.work = &work_student;
  grad->student.person.type_check = &type_check_grad;
  grad->student.graduate = &graduate_grad;

  return grad;
}

Under* Under_new(char* name, char gender, char* major, int year) {
  Under* under = (Under*) malloc(sizeof(Under));
  under->student.person.name = strdup(name);
  under->student.person.gender = gender;
  under->student.major = strdup(major);
  under->year = year;
  under->student.person.work = &work_student;
  under->student.person.type_check = &type_check_under;
  under->student.graduate = &graduate_under;

  return under;
}

Professor* Person_downcast_Professor(Person* person) {
  if(person->type_check("Professor")) {
    return (Professor*) person;
  } else {
    return NULL;
  }
}

Student* Person_downcast_Student(Person* person) {
  if(person->type_check("Student")) {
    return (Student*) person;
  } else {
    return NULL;
  }
}

Under* Person_downcast_Under(Person* person) {
  if(person->type_check("Under")) {
    return (Under*) person;
  } else {
    return NULL;
  }
}

Grad* Person_downcast_Grad(Person* person) {
  if(person->type_check("Grad")) {
    return (Grad*) person;
  } else {
    return NULL;
  }
}

Under* Student_downcast_Under(Student* student) {
  if(student->person.type_check("Under")) {
    return (Under*) student;
  } else {
    return NULL;
  }
}

Grad* Student_downcast_Grad(Student* student) {
  if(student->person.type_check("Grad")) {
    return (Grad*) student;
  } else {
    return NULL;
  }
}

void work_student(Person* person) {
  Student* student = Person_downcast_Student(person);
  printf("%s studies %s.\n", student->person.name, student->major);
}

void work_professor(Person* person) {
  printf("%s teaches.\n", person->name);
}

void graduate_grad(Student* student) {
  Grad* grad = Student_downcast_Grad(student);
  printf("%s graduates with a %s and finds a job in %s.\n", student->person.name, grad->degree, student->major);
}

void graduate_under(Student* student) {
  Under* under = Student_downcast_Under(student);
  printf("%s graduates in %d years and finds a job in %s or goes to grad school.\n", student->person.name, under->year, student->major);
}

void research(Professor* professor, char* topic) {
  printf("%s does reasearch in %s.\n", professor->person.name, topic);
}

int type_check_professor(const char* type) {
  return strcmp(type, "Person") == 0 || strcmp(type, "Professor") == 0;
}

int type_check_grad(const char* type) {
  return strcmp(type, "Person") == 0 || strcmp(type, "Student") == 0 || strcmp(type, "Grad") == 0;
}

int type_check_under(const char* type) {
  return strcmp(type, "Person") == 0 || strcmp(type, "Student") == 0 || strcmp(type, "Under") == 0;
}
