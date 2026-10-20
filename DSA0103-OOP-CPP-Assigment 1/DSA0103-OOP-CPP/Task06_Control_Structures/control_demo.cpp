#include <iostream>
#include <vector>
enum class Zone { Inner, Middle, Outer };
// returns -1 for invalid input
long long fare(Zone z, int hour) {
    if (hour < 0 || hour > 23) return -1;
    long long base;
    switch (z) {
        case Zone::Inner:  base = 1000; break;
        case Zone::Middle: base = 2000; break;
        case Zone::Outer:  base = 3000; break;
        default: return -1;
    }
    bool peak = (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    return peak ? base + base * 20 / 100 : base;
}
int main() {
    std::vector<int> hours = {7, 8, 9, 10, 16, 17, 19, 20, 24, -1};
    for (int h : hours) {                    // range-based for
        long long f = fare(Zone::Middle, h);
        if (f < 0) { std::cout << "hour " << h << ": INVALID, skipped\n"; continue; }
        std::cout << "hour " << h << ": Middle fare = " << f << " paise\n";
    }
    int i = 0;                               // while loop with break
    while (true) { if (fare(Zone::Inner, i) == 1200) break; ++i; }
    std::cout << "First peak hour found by while/break: " << i << '\n';
}
