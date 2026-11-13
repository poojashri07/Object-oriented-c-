// Alternative concept: ONE Staff class with a type field and a switch inside pay()
// Also benchmarks virtual-call pay() against switch-based pay().
#include <chrono>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

enum StaffType { PROFESSOR, LAB_ASSISTANT, GUEST };

struct StaffSwitch {                            // every object carries EVERY field
    StaffType   type;
    std::string name;
    int         id;
    double      basic, research;                // unused for GUEST
    double      hours, rate;                    // unused for PROFESSOR / LAB_ASSISTANT
    double pay() const {
        switch (type) {
            case PROFESSOR:     return basic + basic * 0.42 + research;
            case LAB_ASSISTANT: return basic + basic * 0.42;
            case GUEST:         return hours * rate;
        }
        return 0;
    }
};

struct Base { virtual ~Base() = default; virtual double pay() const = 0; };
struct P : Base { double b = 80000, r = 5000;  double pay() const override { return b + b * 0.42 + r; } };
struct L : Base { double b = 30000;            double pay() const override { return b + b * 0.42; } };
struct G : Base { double h = 40, r = 1500;     double pay() const override { return h * r; } };

int main()
{
    const int N = 3000000;
    std::vector<StaffSwitch> a;  std::vector<std::unique_ptr<Base>> b;
    for (int i = 0; i < N; ++i) {
        int t = i % 3;
        a.push_back({static_cast<StaffType>(t), "x", i, 80000, 5000, 40, 1500});
        if (t == 0) b.push_back(std::make_unique<P>());
        else if (t == 1) b.push_back(std::make_unique<L>());
        else b.push_back(std::make_unique<G>());
    }
    using clk = std::chrono::steady_clock;
    double s1 = 0, s2 = 0;
    auto t0 = clk::now();  for (const auto& x : a) s1 += x.pay();
    auto t1 = clk::now();  for (const auto& x : b) s2 += x->pay();
    auto t2 = clk::now();
    if (s1 + s2 < 0) std::cout << "";            // keep the sums alive so the loops are not optimised away
    std::cout << "sizeof(StaffSwitch)  = " << sizeof(StaffSwitch) << " bytes (all fields in every object)\n";
    std::cout << "sizeof(Professor-like P)    = " << sizeof(P) << " bytes (incl. vptr)\n";
    std::cout << "sizeof(LabAssistant-like L) = " << sizeof(L) << " bytes (incl. vptr)\n";
    std::cout << "sizeof(GuestFaculty-like G) = " << sizeof(G) << " bytes (incl. vptr)\n";
    std::cout << "switch  : " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms\n";
    std::cout << "virtual : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";
    std::cout << "Places to change for a new type: switch design = enum + pay() switch + fields (existing class edited);\n"
                 "virtual design = one NEW class only.\n";
}
