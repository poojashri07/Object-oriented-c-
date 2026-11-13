// Task 2.3 - class declarations for the university hierarchy (virtual base resolves the diamond)
#include <iostream>
#include <string>

class Fellowship {                              // has-a (member class) of ResearchScholar
    std::string agency_; double amount_;
public:
    Fellowship(const std::string& a, double m) : agency_(a), amount_(m) {}
    std::string str() const { return agency_ + " Rs." + std::to_string(static_cast<long>(amount_)); }
};

class Person {
    std::string name_; int id_; std::string phone_;
public:
    Person(const std::string& n, int id, const std::string& ph) : name_(n), id_(id), phone_(ph) {}
    virtual ~Person() = default;
    const std::string& name()  const { return name_; }
    int                id()    const { return id_; }
    const std::string& phone() const { return phone_; }
};

class Student : public virtual Person {         // public: a Student IS-A Person
    std::string programme_; double cgpa_;
public:
    Student(const std::string& n, int id, const std::string& ph, const std::string& prog, double g)
        : Person(n, id, ph), programme_(prog), cgpa_(g) {}
    const std::string& programme() const { return programme_; }
    double cgpa() const { return cgpa_; }
};

class Staff : public virtual Person {           // public: a Staff IS-A Person
    std::string dept_; double salary_;
public:
    Staff(const std::string& n, int id, const std::string& ph, const std::string& d, double s)
        : Person(n, id, ph), dept_(d), salary_(s) {}
    const std::string& dept() const { return dept_; }
    double salary() const { return salary_; }
};

class TeachingAssistant : public Student, public Staff {   // multiple + hybrid (diamond)
public:
    TeachingAssistant(const std::string& n, int id, const std::string& ph,
                      const std::string& prog, double g, const std::string& d, double s)
        : Person(n, id, ph), Student(n, id, ph, prog, g), Staff(n, id, ph, d, s) {}
};

class ResearchScholar : public Student {                    // single inheritance (multilevel from Person)
    Fellowship fellowship_;                                 // has-a
public:
    ResearchScholar(const std::string& n, int id, const std::string& ph, const std::string& prog,
                    double g, const std::string& agency, double amt)
        : Person(n, id, ph), Student(n, id, ph, prog, g), fellowship_(agency, amt) {}
    std::string fellowship() const { return fellowship_.str(); }
};

int main()
{
    TeachingAssistant ta("Kavya", 3001, "9876500001", "M.Tech", 8.7, "CSE", 25000);
    std::cout << "TA   : " << ta.name() << " (" << ta.id() << ") " << ta.programme()
              << " CGPA " << ta.cgpa() << ", " << ta.dept() << " Rs." << ta.salary() << '\n';
    // ta.name() is unambiguous: only ONE Person sub-object exists.
    ResearchScholar rs("Arun", 4001, "9876500002", "Ph.D", 9.1, "UGC-JRF", 31000);
    std::cout << "RS   : " << rs.name() << " (" << rs.id() << ") " << rs.programme()
              << ", fellowship " << rs.fellowship() << '\n';
    Person* p = &ta;                           // implicit upcast is legal because the base is unique
    std::cout << "Upcast: " << p->name() << '\n';
}
