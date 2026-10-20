#include <iostream>
int main() {
    int x = 6, y = 4;
    std::cout << x + y * 3 << ' ' << (x + y) * 3 << '\n';
    int z = x++ + ++y;
    std::cout << z << ' ' << x << ' ' << y << '\n';
    std::cout << (x > y ? x : y) << ' ' << x % 5 * 3 << '\n';
    std::cout << 17 / 5 << ' ' << 17 % 5 << ' ' << -17 / 5 << ' ' << -17 % 5 << '\n';
    int k = 0;
    for (int i = 1; i <= 10; i += 3) k += i;
    std::cout << k << '\n';
}
