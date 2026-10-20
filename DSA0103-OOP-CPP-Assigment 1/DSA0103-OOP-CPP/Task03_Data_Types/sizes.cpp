#include <climits>
#include <iostream>
int main() {
    std::cout << "sizeof(bool)      = " << sizeof(bool) << " byte(s)\n";
    std::cout << "sizeof(char)      = " << sizeof(char) << " byte(s)\n";
    std::cout << "sizeof(int)       = " << sizeof(int) << " byte(s)\n";
    std::cout << "sizeof(long long) = " << sizeof(long long) << " byte(s)\n";
    std::cout << "sizeof(float)     = " << sizeof(float) << " byte(s)\n";
    std::cout << "sizeof(double)    = " << sizeof(double) << " byte(s)\n";
    std::cout << "INT_MAX           = " << INT_MAX << '\n';
    std::cout << "LLONG_MAX         = " << LLONG_MAX << '\n';
    long long worst = 3000000LL * 3600LL;   // 3,000,000 trips x Rs 36 in paise
    std::cout << "Worst daily total = " << worst << " paise ("
              << (worst > INT_MAX ? "exceeds" : "fits in") << " INT_MAX)\n";
}
