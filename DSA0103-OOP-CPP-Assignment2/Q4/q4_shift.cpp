#include <iostream>

class SavingsAccount {
    static const int MAX = 10;     // change to 50 for the Design Decision
    long   accNo;
    double balance;
    double txn[MAX];               // signed: + deposit, - withdrawal
    int    count;                  // number of valid entries (0..MAX)
    void   record(double t);       // private helper
public:
    SavingsAccount(long no, double opening)          // defined inside the class
        : accNo(no), balance(opening), count(0) {}
    double getBalance() const { return balance; }    // defined inside the class
    void   deposit(double amt);                      // defined outside (scope resolution)
    bool   withdraw(double amt);
    void   miniStatement() const;
};

void SavingsAccount::record(double t)
{
    if (count == MAX) {                              // 11th transaction: shift left, drop oldest
        for (int i = 1; i < MAX; ++i) txn[i - 1] = txn[i];
        txn[MAX - 1] = t;
    } else {
        txn[count++] = t;
    }
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
        std::cout << "  " << (txn[i] >= 0 ? "CR " : "DR ")
                  << (txn[i] >= 0 ? txn[i] : -txn[i]) << '\n';
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