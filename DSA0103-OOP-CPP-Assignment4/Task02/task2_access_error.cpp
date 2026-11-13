// EXPECTED TO FAIL: a private member of the base is not accessible in the derived class, whatever the inheritance.
class Person { private: int priv = 3; };
class Student : public Person { public: int bad() const { return priv; } };   // error: 'int Person::priv' is private
int main() { return Student().bad(); }
