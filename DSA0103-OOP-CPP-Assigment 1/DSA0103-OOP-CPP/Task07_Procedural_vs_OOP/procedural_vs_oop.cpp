#include <iostream>
constexpr long long MIN_BAL = 5000;
// ---- procedural ----
bool deductProcedural(long long& balance, long long fare) {
    if (fare < 0 || balance - fare < MIN_BAL) return false;
    balance -= fare; return true;
}
// ---- object-oriented ----
class SmartCard {
    long long balancePaise_;
public:
    explicit SmartCard(long long initial) : balancePaise_(initial >= 0 ? initial : 0) {}
    long long balance() const { return balancePaise_; }
    bool deduct(long long fare) {
        if (fare < 0 || balancePaise_ - fare < MIN_BAL) return false;
        balancePaise_ -= fare; return true;
    }
};
int main() {
    long long bal = 6000;
    std::cout << std::boolalpha << "Procedural deduct(1000): " << deductProcedural(bal, 1000) << ", balance " << bal << '\n';
    bal = -100;                               // procedural: nothing stops this!
    std::cout << "Procedural balance after careless write: " << bal << " paise (invariant broken)\n";
    SmartCard c(6000);
    // c.balancePaise_ = -100;                // would not compile: member is private
    std::cout << "OO deduct(1000): " << c.deduct(1000) << ", balance " << c.balance() << '\n';
    std::cout << "OO deduct(1000): " << c.deduct(1000) << ", balance " << c.balance() << " (blocked)\n";
    SmartCard neg(-500);
    std::cout << "OO constructor with -500 -> " << neg.balance() << '\n';
}
