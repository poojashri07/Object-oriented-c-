// Alternative: std::vector<std::unique_ptr<Account>> instead of raw pointers deleted by hand.
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

class Account {
public:
    Account() = default;
    Account(const Account&) = delete;
    virtual ~Account() { std::cout << "  ~Account\n"; }
    virtual double rate() const { return 3.5; }
};
class SeniorAccount : public Account {
    std::unique_ptr<double[]> history = std::make_unique<double[]>(100);   // RAII member too
public:
    double rate() const override { return 4.0; }
    ~SeniorAccount() override { std::cout << "  ~SeniorAccount\n"; }
};

int main()
{
    {
        std::vector<std::unique_ptr<Account>> v;
        v.push_back(std::make_unique<Account>());
        v.push_back(std::make_unique<SeniorAccount>());
        for (const auto& a : v) std::cout << a->rate() << '\n';
    }                                                                       // everything freed automatically
    std::cout << "sizeof(raw Account*) = " << sizeof(Account*) << ", sizeof(unique_ptr<Account>) = "
              << sizeof(std::unique_ptr<Account>) << '\n';

    const int N = 2000000;
    using clk = std::chrono::steady_clock;
    struct Plain { virtual ~Plain() = default; virtual double rate() const { return 3.5; } };   // silent class for timing
    std::vector<Plain*> raw; std::vector<std::unique_ptr<Plain>> smart;
    for (int i = 0; i < N; ++i) { raw.push_back(new Plain); smart.push_back(std::make_unique<Plain>()); }
    double s1 = 0, s2 = 0;
    auto t0 = clk::now(); for (auto* a : raw)   s1 += a->rate();
    auto t1 = clk::now(); for (auto& a : smart) s2 += a->rate();
    auto t2 = clk::now();
    std::cout << "raw pointers : " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms\n";
    std::cout << "unique_ptr   : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";
    for (auto* a : raw) delete a;
    std::cout << (s1 == s2 ? "same results\n" : "DIFFERENT\n");
}
