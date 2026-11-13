// Alternative: TeachingAssistant HAS-A Student and HAS-A Staff (composition)
#include <iostream>
#include <string>

struct Person { std::string name; int id; std::string phone; };
struct StudentV : virtual Person { std::string programme; double cgpa = 0; };
struct StaffV   : virtual Person { std::string dept;      double salary = 0; };
struct TA_Inherit : StudentV, StaffV {};                  // virtual-base design

struct StudentC : Person { std::string programme; double cgpa = 0; };
struct StaffC   : Person { std::string dept;      double salary = 0; };
struct TA_Compose { StudentC student; StaffC staff; };    // has-a design: TWO Person copies

int main()
{
    std::cout << "sizeof(Person)                  = " << sizeof(Person) << '\n';
    std::cout << "sizeof(TA_Inherit) virtual base = " << sizeof(TA_Inherit) << '\n';
    std::cout << "sizeof(TA_Compose) composition  = " << sizeof(TA_Compose) << '\n';

    TA_Inherit a;  a.name = "Kavya";                      // one name, one access path
    std::cout << "inheritance : a.name = " << a.name << '\n';

    TA_Compose c;  c.student.name = "Kavya";  c.staff.name = "Kavya";   // two copies to keep in sync
    std::cout << "composition : c.student.name = " << c.student.name
              << ", c.staff.name = " << c.staff.name << "  (two independent copies)\n";
    c.student.name = "Kavya S.";
    std::cout << "after editing student copy: staff copy still = " << c.staff.name << "  <-- inconsistency risk\n";
    // Also: a TA_Compose is NOT a Person, so it cannot be passed to a function taking Person&.
}
