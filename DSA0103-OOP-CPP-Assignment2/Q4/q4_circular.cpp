#include <iostream>

class SavingsAccount {
    static const int MAX = 10;     // change to 50 for the Design Decision
    long   accNo;
    double balance;
    double txn[MAX];               // signed: + deposit, - withdrawal
    int    start;
    int    count;
    void   record(double t);       // private helper
public:
    SavingsAccount(long no, double opening)          // defined inside the class
        : accNo(no), balance(opening), start(0), count(0) {}
    double getBalance() const { return balance; }    // defined inside the class
    void   deposit(double amt);                      // defined outside (scope resolution)
    bool   withdraw(double amt);
    void   miniStatement() const;
};

void SavingsAccount::record(double t)
{
    txn[(start + count) % MAX] = t;
    if (count < MAX) ++count; else start = (start + 1) % MAX;
}
void SavingsAccount::deposit(double amt)
{
    if (amt <= 0) return;
    balance += amt;
    record(amt);
}
bool SavingsAccount::withdraw(double amt)
{
    if (amt <= 0 || amt > balance) return false;
    balance -= amt;
    record(-amt);
    return true;
}
void SavingsAccount::miniStatement() const
{
    std::cout << "Mini-statement for " << accNo << '\n';
    for (int i = 0; i < count; ++i)
        std::cout << "  " << (txn[(start+i)%MAX] >= 0 ? "CR " : "DR ")
                  << ((txn[(start+i)%MAX] >= 0 ? txn[(start+i)%MAX] : -txn[(start+i)%MAX])) << '\n';
    std::cout << "  Balance: " << balance << '\n';
}

int main()
{
    SavingsAccount a(1001, 5000);
    for (int i = 1; i <= 12; ++i) {            // 12 transactions: first two must disappear
        if (i % 3 == 0) a.withdraw(100 * i);
        else            a.deposit(100 * i);
    }
    a.miniStatement();
}