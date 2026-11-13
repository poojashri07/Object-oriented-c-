// Without 'virtual' the diamond has TWO Person sub-objects -> unqualified access is ambiguous.
// This file is EXPECTED to fail to compile (evidence for Task 2.2).
#include <iostream>
#include <string>
struct Person  { std::string name = "Asha"; };
struct Student : Person {};
struct Staff   : Person {};
struct TeachingAssistant : Student, Staff {};
int main()
{
    TeachingAssistant ta;
    std::cout << ta.name << '\n';               // ERROR: request for member 'name' is ambiguous
}
