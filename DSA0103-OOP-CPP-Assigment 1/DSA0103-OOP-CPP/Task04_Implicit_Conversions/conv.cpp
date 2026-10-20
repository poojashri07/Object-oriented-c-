#include <iostream>
int main() {
    int a = 9, b = 4;
    double c = a / b;                         // integer division first
    double d = static_cast<double>(a) / b;    // real division
    std::cout << c << ' ' << d << '\n';
    char ch = 'B' + 3;
    std::cout << ch << ' ' << ch + 1 << '\n';
    bool flag = -7;
    std::cout << flag << ' ' << std::boolalpha << flag << '\n';
    unsigned int u = 2;
    int s = -2;
    std::cout << (s < u ? "s < u" : "s >= u") << '\n';
    int safeCount{3};
    std::cout << "safeCount = " << safeCount << '\n';
    double price = 19.99;
    int truncated = static_cast<int>(price);
    std::cout << "static_cast<int>(19.99) = " << truncated << '\n';
}
