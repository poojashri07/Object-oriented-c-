// Tasks 3.1 - 3.3 : constructors in derived classes, member classes, order of construction/destruction
#include <iostream>
#include <string>

class Address {                                           // member class of Person
    std::string city_; int pin_;
public:
    Address(const std::string& c, int p) : city_(c), pin_(p) { std::cout << "  Address(" << c << ")\n"; }
    ~Address() { std::cout << "  ~Address\n"; }
};

class Course {                                            // member class of Student
    std::string title_; int credits_;
public:
    Course(const std::string& t, int cr) : title_(t), credits_(cr) { std::cout << "  Course(" << t << ")\n"; }
    ~Course() { std::cout << "  ~Course\n"; }
};

class Person {
    std::string name_; int id_; Address addr_;
public:
    Person(const std::string& n, int id, const std::string& city, int pin)
        : name_(n), id_(id), addr_(city, pin) { std::cout << "  Person(" << n << ")\n"; }
    virtual ~Person() { std::cout << "  ~Person\n"; }
};

class Student : public virtual Person {
    Course course_; double cgpa_;
public:
    Student(const std::string& n, int id, const std::string& city, int pin,
            const std::string& ct, int cr, double g)
        : Person(n, id, city, pin), course_(ct, cr), cgpa_(g) { std::cout << "  Student\n"; }
    ~Student() { std::cout << "  ~Student\n"; }
};

class Staff : public virtual Person {
    std::string dept_; double salary_;
public:
    Staff(const std::string& n, int id, const std::string& city, int pin,
          const std::string& d, double s)
        : Person(n, id, city, pin), dept_(d), salary_(s) { std::cout << "  Staff\n"; }
    ~Staff() { std::cout << "  ~Staff\n"; }
};

class TeachingAssistant : public Student, public Staff {
public:
    // Most-derived class calls the VIRTUAL base constructor directly (Student/Staff calls to Person are skipped)
    TeachingAssistant(const std::string& n, int id, const std::string& city, int pin,
                      const std::string& ct, int cr, double g, const std::string& d, double s)
        : Person(n, id, city, pin), Student(n, id, city, pin, ct, cr, g), Staff(n, id, city, pin, d, s)
    { std::cout << "  TeachingAssistant\n"; }
    ~TeachingAssistant() { std::cout << "  ~TeachingAssistant\n"; }
};

int main()
{
    std::cout << "--- Student object ---\n";
    { Student s("Kavya", 1, "Salem", 636001, "OOP", 4, 8.9); }
    std::cout << "--- Staff object ---\n";
    { Staff f("Ravi", 2, "Chennai", 600001, "CSE", 50000); }
    std::cout << "--- TeachingAssistant object ---\n";
    { TeachingAssistant t("Asha", 3, "Madurai", 625001, "DSA", 3, 9.1, "IT", 25000); }
}
