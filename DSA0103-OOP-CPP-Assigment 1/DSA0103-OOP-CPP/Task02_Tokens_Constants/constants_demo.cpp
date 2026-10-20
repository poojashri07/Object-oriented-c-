#include <array>
#include <iostream>
enum class Zone { Inner, Middle, Outer };
constexpr long long MIN_BALANCE_PAISE = 5000;
constexpr int PEAK_SURCHARGE_PERCENT = 20;
constexpr std::array<long long, 3> BASE_PAISE = {1000, 2000, 3000};
#define BAD_FARE 10+5          // macro pitfall: no parentheses
int main() {
    std::cout << "Inner base fare (paise): " << BASE_PAISE[static_cast<std::size_t>(Zone::Inner)] << '\n';
    std::cout << "Min balance (paise)    : " << MIN_BALANCE_PAISE << '\n';
    std::cout << "Peak surcharge percent : " << PEAK_SURCHARGE_PERCENT << '\n';
    std::cout << "BAD_FARE * 2 = " << BAD_FARE * 2 << "  (expected 30, macro gives 20)\n";
    std::cout << "(10+5) * 2   = " << (10 + 5) * 2 << '\n';
}
