// Task 4.1 / 4.2 - the DEFECTIVE program with evidence output added to the destructors.
// Compile:  g++ -std=c++17 -Wall -Wextra -g -fsanitize=address -fsanitize-recover=address task4_defects.cpp
// Run:      ASAN_OPTIONS=halt_on_error=0:detect_leaks=1 ./a.out
#include <iostream>
#include <vector>

class Account {
public:
    double rate() const { return 3.5; }                       // NOT virtual -> static binding
    ~Account() { std::cout << "  ~Account\n"; }               // NOT virtual -> derived dtor skipped
};

class SeniorAccount : public Account {
    double* history = new double[100];
public:
    SeniorAccount() { std::cout << "  SeniorAccount() allocates history[100]\n"; }
    double rate() const { return 4.0; }                       // hides, does not override
    ~SeniorAccount() { delete[] history; std::cout << "  ~SeniorAccount frees history\n"; }
};

int main()
{
    Account* accounts[2] = { new Account, new SeniorAccount };
    std::cout << "[1] rates through base pointers:\n";
    for (Account* a : accounts) std::cout << a->rate() << "\n";   // prints 3.5 and 3.5 (should be 3.5 and 4)

    std::cout << "[2] deleting through base pointers:\n";
    for (Account* a : accounts) delete a;                          // SeniorAccount dtor never runs

    std::cout << "[3] slicing:\n";
    std::vector<Account> v;
    v.push_back(SeniorAccount());                                  // sliced copy stored as plain Account
    std::cout << "stored element rate = " << v[0].rate() << "  (sizeof Account=" << sizeof(Account)
              << ", sizeof SeniorAccount=" << sizeof(SeniorAccount) << ")\n";
}
