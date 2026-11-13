// Task 2.4 - evidence for the access table (public / protected / private inheritance of Person)
#include <iostream>
#include <type_traits>
#include <utility>

class Person {
public:    int pub = 1;
protected: int prot = 2;
private:   int priv = 3;
};

// Derived classes: inside each one, 'pub' and 'prot' can be used; 'priv' cannot (see task2_access_error.cpp)
class StudentPublic    : public    Person { public: int inside() const { return pub + prot; } };
class StudentProtected : protected Person { public: int inside() const { return pub + prot; } };
class StudentPrivate   : private   Person { public: int inside() const { return pub + prot; } };

// Detection traits: can OUTSIDE code (e.g. main) name the member through a Student object?
template <class T, class = void> struct outside_pub  : std::false_type {};
template <class T> struct outside_pub<T, std::void_t<decltype(std::declval<T&>().pub)>> : std::true_type {};
template <class T, class = void> struct outside_prot : std::false_type {};
template <class T> struct outside_prot<T, std::void_t<decltype(std::declval<T&>().prot)>> : std::true_type {};

// Is conversion Student* -> Person* allowed outside the class? (is-a visible to clients)
template <class D> constexpr const char* yn(bool b) { return b ? "accessible" : "NOT accessible"; }

int main()
{
    std::cout << "Inside the derived class (member functions), via public/protected/private inheritance:\n";
    std::cout << "  StudentPublic::inside()    = " << StudentPublic().inside()    << "  (pub and prot usable)\n";
    std::cout << "  StudentProtected::inside() = " << StudentProtected().inside() << "  (pub and prot usable)\n";
    std::cout << "  StudentPrivate::inside()   = " << StudentPrivate().inside()   << "  (pub and prot usable)\n";
    std::cout << "  priv is NOT accessible in any of them (private to Person)\n\n";

    std::cout << "Outside code (main) using a Student object:\n";
    std::cout << "                     Person::pub        Person::prot       Student* -> Person*\n";
    std::cout << "  public inheritance : " << yn<StudentPublic>(outside_pub<StudentPublic>::value) << "    "
              << yn<StudentPublic>(outside_prot<StudentPublic>::value) << "    "
              << (std::is_convertible<StudentPublic*, Person*>::value ? "allowed" : "NOT allowed") << '\n';
    std::cout << "  protected inherit. : " << yn<StudentProtected>(outside_pub<StudentProtected>::value) << "    "
              << yn<StudentProtected>(outside_prot<StudentProtected>::value) << "    "
              << (std::is_convertible<StudentProtected*, Person*>::value ? "allowed" : "NOT allowed") << '\n';
    std::cout << "  private inheritance: " << yn<StudentPrivate>(outside_pub<StudentPrivate>::value) << "    "
              << yn<StudentPrivate>(outside_prot<StudentPrivate>::value) << "    "
              << (std::is_convertible<StudentPrivate*, Person*>::value ? "allowed" : "NOT allowed") << '\n';
}
