// Alternative: Student holds Address* (dynamic) instead of an Address member object.
// Now the class must manage the pointer: constructor allocates, destructor frees, copy must deep-copy (Rule of Three).
#include <chrono>
#include <iostream>
#include <string>

class Address {
    std::string city; int pin;
public:
    Address(const std::string& c, int p) : city(c), pin(p) {}
    std::string str() const { return city + "-" + std::to_string(pin); }
};

class Person {
protected: std::string name; int age;
public: Person(const std::string& n, int a) : name(n), age(a) {}
};

class StudentP : public Person {
    long long regNo;
    Address*  home;                                            // pointer member
public:
    StudentP(const std::string& n, int a, long long r, const std::string& c, int p)
        : Person(n, a), regNo(r), home(new Address(c, p)) {}   // 1. allocate in ctor
    StudentP(const StudentP& o)                                // 2. deep copy ctor
        : Person(o), regNo(o.regNo), home(new Address(*o.home)) {}
    StudentP& operator=(const StudentP& o) {                   //    deep copy assignment
        if (this != &o) { Person::operator=(o); regNo = o.regNo; Address* t = new Address(*o.home); delete home; home = t; }
        return *this;
    }
    ~StudentP() { delete home; }                               // 3. release in dtor
    void print() const { std::cout << regNo << ' ' << name << " (" << age << ") " << home->str() << '\n'; }
};

class StudentM : public Person {                               // member-object version for timing
    long long regNo; Address home;
public:
    StudentM(const std::string& n, int a, long long r, const std::string& c, int p)
        : Person(n, a), regNo(r), home(c, p) {}
    const Address& h() const { return home; }
};

template <class T> inline void keep(T* p) { asm volatile("" : : "g"(p) : "memory"); }   // stop the optimiser deleting the loop

int main()
{
    StudentP s("Kavya", 19, 192311001, "Salem", 636001);
    StudentP t = s;                                            // safe because of deep copy
    t.print();

    std::cout << "sizeof(StudentM) member object = " << sizeof(StudentM) << " bytes\n";
    std::cout << "sizeof(StudentP) pointer member = " << sizeof(StudentP) << " bytes (+ sizeof(Address)=" << sizeof(Address) << " on the heap)\n";

    const int N = 2000000;
    using clk = std::chrono::steady_clock;
    auto t0 = clk::now();
    for (int i = 0; i < N; ++i) { StudentM m("A", 19, i, "Salem", 636001); keep(&m); }
    auto t1 = clk::now();
    for (int i = 0; i < N; ++i) { StudentP p("A", 19, i, "Salem", 636001); keep(&p); }
    auto t2 = clk::now();
    std::cout << N << " constructions, member object : " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms (no heap for Address)\n";
    std::cout << N << " constructions, new Address   : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms (extra heap alloc + free)\n";
}
