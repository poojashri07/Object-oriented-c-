#include <iostream>
#include <string>
std::string rupees(long long paise) {
    std::string s = "Rs " + std::to_string(paise / 100) + ".";
    long long p = paise % 100;
    if (p < 10) s += "0";
    return s + std::to_string(p);
}
int main() { for (long long p : {0LL, 5LL, 1020LL, 5999LL, 10800000000LL}) std::cout << p << " paise = " << rupees(p) << '\n'; }
