#ifndef JAM_PERSON_HPP
#define JAM_PERSON_HPP

typedef struct Person_ {
  char* name;
  char gender;
  void (*work)(Person_*);
  int (*type_check)(const char*);
  void (*delet)(Person_*);
} Person;

typedef struct Professor_ {
  Person person;
  char* office;
  void (*research)(Professor_*, const char*);
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

Professor* Professor_new(const char* name, char gender, const char* office);
Grad* Grad_new(const char* name, char gender, const char* major, const char* degree);
Under* Under_new(const char* name, char gender, const char* major, int year);

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

void Professor_delete(Person* person);
void Under_delete(Person* person);
void Grad_delete(Person* person);

void work_student(Person* person);
void work_professor(Person* person);
void graduate_grad(Student* student);
void graduate_under(Student* student);
void research(Professor* professor, const char* topic);
int type_check_professor(const char* type);
int type_check_grad(const char* type);
int type_check_under(const char* type);

#endif
