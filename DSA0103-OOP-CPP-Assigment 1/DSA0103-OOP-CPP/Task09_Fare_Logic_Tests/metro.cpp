// City Metro Smart-Card Fare Engine  (C++17)
#include <array>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

enum class Zone { Inner, Middle, Outer, Airport };

constexpr long long MIN_BALANCE_PAISE      = 5000;   // Rs 50.00
constexpr int       PEAK_SURCHARGE_PERCENT = 20;
constexpr int       WEEKEND_DISCOUNT_PERCENT = 10;
constexpr std::array<long long, 4> BASE_FARE_PAISE = {1000, 2000, 3000, 6000};

std::string zoneName(Zone z) {
    switch (z) {
        case Zone::Inner:   return "Inner";
        case Zone::Middle:  return "Middle";
        case Zone::Outer:   return "Outer";
        case Zone::Airport: return "Airport";
    }
    return "Unknown";
}

std::string rupees(long long paise) {
    std::string s = "Rs " + std::to_string(paise / 100) + ".";
    long long p = paise % 100;
    if (p < 10) s += "0";
    return s + std::to_string(p);
}

class FarePolicy {
public:
    static bool isPeak(int hour) {
        return (hour >= 8 && hour < 10) || (hour >= 17 && hour < 20);
    }
    // Returns nullopt for invalid input. Weekend discount REPLACES peak surcharge.
    static std::optional<long long> fareFor(Zone zone, int hour, bool weekend,
                                            bool airportEnabled = true) {
        if (hour < 0 || hour > 23) return std::nullopt;
        auto idx = static_cast<std::size_t>(zone);
        if (idx >= BASE_FARE_PAISE.size()) return std::nullopt;
        if (zone == Zone::Airport && !airportEnabled) return std::nullopt;
        long long base = BASE_FARE_PAISE[idx];
        if (weekend)         return base - base * WEEKEND_DISCOUNT_PERCENT / 100;
        if (isPeak(hour))    return base + base * PEAK_SURCHARGE_PERCENT / 100;
        return base;
    }
};

class SmartCard {
    std::string id_;
    long long balancePaise_;
public:
    SmartCard(std::string id, long long initial)
        : id_(std::move(id)), balancePaise_(initial >= 0 ? initial : 0) {}
    long long balance() const { return balancePaise_; }
    const std::string& id() const { return id_; }
    bool canTravel(long long fare) const {
        return fare >= 0 && balancePaise_ - fare >= MIN_BALANCE_PAISE;
    }
    bool deduct(long long fare) {
        if (!canTravel(fare)) return false;
        balancePaise_ -= fare;
        return true;
    }
    bool recharge(long long amount) {
        if (amount <= 0) return false;
        balancePaise_ += amount;
        return true;
    }
};

class MonthlyPass {
    Zone a_, b_;
    int from_, until_;
public:
    MonthlyPass(Zone a, Zone b, int from, int until) : a_(a), b_(b), from_(from), until_(until) {}
    bool covers(Zone z, int day) const {
        return day >= from_ && day <= until_ && (z == a_ || z == b_);
    }
};

struct FareCase { std::string name; Zone zone; int hour; bool weekend; long long expected; };

int main() {
    std::cout << "=== PART 1: Table-driven fare tests ===\n";
    std::vector<FareCase> cases = {
        {"T1  Inner  07:00 weekday", Zone::Inner,   7,  false, 1000},
        {"T2  Inner  08:00 weekday", Zone::Inner,   8,  false, 1200},
        {"T3  Middle 09:00 weekday", Zone::Middle,  9,  false, 2400},
        {"T4  Middle 10:00 weekday", Zone::Middle,  10, false, 2000},
        {"T5  Outer  17:00 weekday", Zone::Outer,   17, false, 3600},
        {"T6  Outer  19:59 weekday", Zone::Outer,   19, false, 3600},
        {"T7  Outer  20:00 weekday", Zone::Outer,   20, false, 3000},
        {"T8  Airport 08:00 weekday", Zone::Airport, 8, false, 7200},
        {"T9  Airport 08:00 weekend", Zone::Airport, 8, true,  5400},
        {"T10 Inner  12:00 weekend", Zone::Inner,   12, true,  900},
    };
    int pass = 0;
    for (const auto& c : cases) {
        auto f = FarePolicy::fareFor(c.zone, c.hour, c.weekend);
        bool ok = f && *f == c.expected;
        pass += ok;
        std::cout << std::left << std::setw(28) << c.name << " expected " << std::setw(9)
                  << rupees(c.expected) << " actual " << std::setw(9)
                  << (f ? rupees(*f) : "INVALID") << (ok ? " PASS\n" : " FAIL\n");
    }
    std::cout << pass << "/" << cases.size() << " fare tests passed\n";

    std::cout << "\n=== PART 2: Invalid input tests ===\n";
    auto bad1 = FarePolicy::fareFor(Zone::Inner, 24, false);
    auto bad2 = FarePolicy::fareFor(Zone::Inner, -1, false);
    auto bad3 = FarePolicy::fareFor(static_cast<Zone>(9), 10, false);
    std::cout << "hour 24      -> " << (bad1 ? "accepted (BUG)" : "rejected") << '\n';
    std::cout << "hour -1      -> " << (bad2 ? "accepted (BUG)" : "rejected") << '\n';
    std::cout << "zone value 9 -> " << (bad3 ? "accepted (BUG)" : "rejected") << '\n';

    std::cout << "\n=== PART 3: SmartCard boundary tests ===\n";
    SmartCard c1("C-001", 6000);
    std::cout << "Rs 60.00, Rs 10.00 fare -> " << (c1.deduct(1000) ? "approved" : "denied")
              << ", balance " << rupees(c1.balance()) << '\n';
    SmartCard c2("C-002", 5999);
    std::cout << "Rs 59.99, Rs 10.00 fare -> " << (c2.deduct(1000) ? "approved" : "denied")
              << ", balance " << rupees(c2.balance()) << '\n';
    SmartCard c3("C-003", 10000);
    std::cout << "recharge(-100)  -> " << (c3.recharge(-100) ? "accepted" : "rejected")
              << ", balance " << rupees(c3.balance()) << '\n';
    std::cout << "recharge(2500)  -> " << (c3.recharge(2500) ? "accepted" : "rejected")
              << ", balance " << rupees(c3.balance()) << '\n';
    SmartCard c4(  "C-004", -500);
    std::cout << "constructor with -500 paise -> balance " << rupees(c4.balance()) << '\n';

    std::cout << "\n=== PART 4: Five-journey simulation (start Rs 150.00) ===\n";
    SmartCard card("C-100", 15000);
    struct Trip { Zone z; int h; };
    std::vector<Trip> trips = {{Zone::Middle, 9}, {Zone::Outer, 14}, {Zone::Outer, 18},
                               {Zone::Inner, 8}, {Zone::Inner, 21}};
    int n = 1;
    long long collected = 0;
    for (const auto& t : trips) {
        auto f = FarePolicy::fareFor(t.z, t.h, false);
        std::cout << "Trip " << n++ << ": " << std::setw(6) << zoneName(t.z) << " at "
                  << std::right << std::setfill('0') << std::setw(2) << t.h << ":00" << std::setfill(' ') << std::left
                  << "  fare " << rupees(*f) << "  -> ";
        if (card.deduct(*f)) { collected += *f; std::cout << "APPROVED, balance " << rupees(card.balance()) << '\n'; }
        else std::cout << "DENIED,   balance " << rupees(card.balance()) << '\n';
    }
    std::cout << "Total collected: " << rupees(collected) << ", final balance: " << rupees(card.balance()) << '\n';

    std::cout << "\n=== PART 5: MonthlyPass tests (Inner+Middle, days 1-30) ===\n";
    MonthlyPass pass1(Zone::Inner, Zone::Middle, 1, 30);
    std::cout << "Inner,  day 15 covered: " << std::boolalpha << pass1.covers(Zone::Inner, 15) << '\n';
    std::cout << "Outer,  day 15 covered: " << pass1.covers(Zone::Outer, 15) << '\n';
    std::cout << "Middle, day 31 covered: " << pass1.covers(Zone::Middle, 31) << '\n';
    return 0;
}
