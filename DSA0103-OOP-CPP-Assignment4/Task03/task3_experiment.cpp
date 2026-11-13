// Task 3.4 - experiment.  Build twice:
//   g++ -std=c++17 -Wall -Wextra -DUSE_VIRTUAL task3_experiment.cpp   (virtual bases)
//   g++ -std=c++17 -Wall -Wextra               task3_experiment.cpp   (ordinary bases)
#include <iostream>
#include <string>

struct Person {
    std::string name;
    Person(const std::string& n) : name(n) { std::cout << "Person(" << n << ") "; }
};

#ifdef USE_VIRTUAL
struct Student : virtual Person { Student(const std::string& n) : Person(n) { std::cout << "Student "; } };
struct Staff   : virtual Person { Staff(const std::string& n)   : Person(n) { std::cout << "Staff ";   } };
struct TeachingAssistant : Student, Staff {
    TeachingAssistant(const std::string& n) : Person(n), Student(n), Staff(n) { std::cout << "TA "; }
};
#else
struct Student : Person { Student(const std::string& n) : Person(n) { std::cout << "Student "; } };
struct Staff   : Person { Staff(const std::string& n)   : Person(n) { std::cout << "Staff ";   } };
struct TeachingAssistant : Student, Staff {
    TeachingAssistant(const std::string& n) : Student(n), Staff(n) { std::cout << "TA "; }
};
#endif

int main()
{
    TeachingAssistant ta("Asha");
    std::cout << '\n';
#ifdef USE_VIRTUAL
    std::cout << "virtual bases : ";
#else
    std::cout << "plain bases   : ";
#endif
    std::cout << "sizeof(Person)=" << sizeof(Person) << " sizeof(Student)=" << sizeof(Student)
              << " sizeof(TeachingAssistant)=" << sizeof(TeachingAssistant) << '\n';
}
