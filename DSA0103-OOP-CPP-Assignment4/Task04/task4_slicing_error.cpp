// Expected to FAIL to compile: shows the repaired base class refusing to be sliced.
#include <iostream>
class Account {
public:
    Account() = default;
    Account(const Account&) = delete;
    virtual ~Account() = default;
    virtual double rate() const { return 3.5; }
};
class SeniorAccount : public Account { public: double rate() const override { return 4.0; } };
int main()
{
    Account copy = SeniorAccount();      // error: use of deleted function
    std::cout << copy.rate() << '\n';
}
