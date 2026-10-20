#include <climits>
#include <iomanip>
#include <iostream>
#include <vector>
int main() {
    // Part A: 0.10 added 10,000,000 times (Rs 0.10 = 10 paise)
    long long p = 0; double d = 0.0; float fl = 0.0f;
    for (int i = 0; i < 10000000; ++i) { p += 10; d += 0.10; fl += 0.10f; }
    std::cout << std::fixed << std::setprecision(6);
    std::cout << "Integer paise total : " << p << " paise = Rs " << p / 100.0 << "\n";
    std::cout << "double total        : Rs " << d << "   error = " << (d - 1000000.0) << "\n";
    std::cout << "float total         : Rs " << fl << "   error = " << (fl - 1000000.0f) << "\n";

    // Part B: one day, 3,000,000 journeys, mixed fares
    const long long fares[] = {1000, 1200, 2000, 2400, 3000, 3600};
    long long total = 0; double totalRs = 0.0;
    for (long long i = 0; i < 3000000; ++i) {
        long long f = fares[i % 6];
        total += f; totalRs += f / 100.0;
    }
    std::cout << "\n3,000,000 journeys, fares cycle Rs 10/12/20/24/30/36\n";
    std::cout << "long long paise : " << total << " (Rs " << total / 100 << "." << std::setw(2) << std::setfill('0') << total % 100 << ")\n";
    std::cout << std::setfill(' ');
    std::cout << "double rupees   : " << std::setprecision(6) << totalRs << "\n";
    std::cout << "paise total > INT_MAX ? " << std::boolalpha << (total > INT_MAX) << "  (INT_MAX = " << INT_MAX << ")\n";

    // Part C: scale table
    std::cout << "\nDaily collection at Rs 30 per journey:\n";
    for (long long n : {20000LL, 500000LL, 3000000LL})
        std::cout << std::setw(8) << n << " journeys -> Rs " << n * 30 << "\n";
}
