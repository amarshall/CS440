#ifndef JAM_PERSON_HPP
#define JAM_PERSON_HPP

typedef struct Person_ {
  char* name;
  char gender;
  void (*work)(Person_*);
  int (*type_check)(const char*);
} Person;

typedef struct Professor_ {
  Person person;
  char* office;
  void (*research)(Professor_*, char*);
} Professor;

typedef struct Student_ {
  Person person;
  char* major;
  void (*graduate)(Student_*);
} Student;

typedef struct {
  Student student;
  int year;
} Under;

typedef struct {
  Student student;
  char* degree;
} Grad;

Professor* Professor_new(char* name, char gender, char* office);
Grad* Grad_new(char* name, char gender, char* major, char* degree);
Under* Under_new(char* name, char gender, char* major, int year);

Professor* Person_downcast_Professor(Person* person);
Student* Person_downcast_Student(Person* person);
Under* Person_downcast_Under(Person* person);
Grad* Person_downcast_Grad(Person* person);
Under* Student_downcast_Under(Student* student);
Grad* Student_downcast_Grad(Student* student);

void Person_print(Person* person);
void Professor_print(Professor* professor);
void Student_print(Student* student);
void Under_print(Under* under);

void work_student(Person* person);
void work_professor(Person* person);
void graduate_grad(Student* student);
void graduate_under(Student* student);
void research(Professor* professor, char* topic);
int type_check_professor(const char* type);
int type_check_grad(const char* type);
int type_check_under(const char* type);

#endif
