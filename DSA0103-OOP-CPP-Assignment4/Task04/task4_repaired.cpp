// Task 4.3 - repaired program: virtual functions + override, virtual destructor, no slicing.
// Compile: g++ -std=c++17 -Wall -Wextra -g -fsanitize=address task4_repaired.cpp
#include <iostream>
#include <vector>

class Account {
public:
    Account() = default;
    Account(const Account&) = delete;                         // rule 2: copying a polymorphic base is blocked,
    Account& operator=(const Account&) = delete;              //         so slicing cannot compile
    virtual ~Account() { std::cout << "  ~Account\n"; }       // rule 1: virtual destructor
    virtual double rate() const { return 3.5; }               // virtual
};

class SeniorAccount : public Account {
    double* history = new double[100];
public:
    SeniorAccount() { std::cout << "  SeniorAccount() allocates history[100]\n"; }
    double rate() const override { return 4.0; }              // override checked by compiler
    ~SeniorAccount() override { delete[] history; std::cout << "  ~SeniorAccount frees history\n"; }
};

int main()
{
    Account* accounts[2] = { new Account, new SeniorAccount };
    std::cout << "[1] rates through base pointers:\n";
    for (Account* a : accounts) std::cout << a->rate() << "\n";   // 3.5 then 4

    std::cout << "[2] deleting through base pointers:\n";
    for (Account* a : accounts) delete a;                          // both destructors run

    std::cout << "[3] polymorphic storage without slicing (pointers, not copies):\n";
    std::vector<Account*> v;
    v.push_back(new SeniorAccount);
    std::cout << "stored element rate = " << v[0]->rate() << '\n';
    for (Account* a : v) delete a;
    // Account copy = SeniorAccount();      // would now be a COMPILE ERROR (copy constructor deleted)
}
