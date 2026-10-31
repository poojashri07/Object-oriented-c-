#include <iostream>
struct Student { char name[64]; long long fee; int marks[100]; };
int main() { std::cout << "sizeof(long long) = " << sizeof(long long) << ", sizeof(Student) = " << sizeof(Student) << ", sizeof(Student*) = " << sizeof(Student*) << '\n'; }
