// Alternative: ONE Vehicle class with a type code and a switch in charge().
#include <chrono>
#include <iostream>
#include <memory>
#include <vector>

enum VType { BICYCLE, TWO_WHEELER, CAR, ELECTRIC_CAR };

struct VehicleSwitch {                                  // every object carries EVERY field
    VType type; double dailyRate; double energy; int seats; double batteryKWh; int serviceKey;
    double charge(int planned, int late, double used) const {
        switch (type) {
            case BICYCLE:      return dailyRate * planned + dailyRate * 1.5 * late;
            case TWO_WHEELER:  return dailyRate * planned + dailyRate * 2.0 * late + used * 105.0;
            case CAR:          return dailyRate * planned + dailyRate * 2.0 * late + used * 105.0;
            case ELECTRIC_CAR: return dailyRate * planned + dailyRate * 2.0 * late + used * 9.0;
        }
        return 0;                                       // adding ELECTRIC_BUS => edit enum AND this switch
    }
};

struct VB { virtual ~VB() = default; virtual double charge(int, int, double) const = 0; };
struct VBi : VB { double r = 150;  double charge(int p, int l, double)   const override { return r * p + r * 1.5 * l; } };
struct VT  : VB { double r = 400;  double charge(int p, int l, double u) const override { return r * p + r * 2.0 * l + u * 105.0; } };
struct VC  : VB { double r = 1800; double charge(int p, int l, double u) const override { return r * p + r * 2.0 * l + u * 105.0; } };
struct VE  : VB { double r = 2500; double charge(int p, int l, double u) const override { return r * p + r * 2.0 * l + u * 9.0; } };

int main()
{
    const int N = 4000000;
    std::vector<VehicleSwitch> a; std::vector<std::unique_ptr<VB>> b;
    for (int i = 0; i < N; ++i) {
        int t = i % 4;
        static const double R[4] = {150, 400, 1800, 2500};
        a.push_back({static_cast<VType>(t), R[t], 0, 4, 40, 20261113});
        if (t == 0) b.push_back(std::make_unique<VBi>()); else if (t == 1) b.push_back(std::make_unique<VT>());
        else if (t == 2) b.push_back(std::make_unique<VC>()); else b.push_back(std::make_unique<VE>());
    }
    using clk = std::chrono::steady_clock;
    double s1 = 0, s2 = 0;
    auto t0 = clk::now(); for (const auto& x : a) s1 += x.charge(3, 1, 10);
    auto t1 = clk::now(); for (const auto& x : b) s2 += x->charge(3, 1, 10);
    auto t2 = clk::now();
    std::cout << "sizeof(VehicleSwitch) = " << sizeof(VehicleSwitch) << " bytes per vehicle (all fields always present)\n";
    std::cout << "sizeof(VBi)=" << sizeof(VBi) << " sizeof(VT)=" << sizeof(VT) << " sizeof(VC)=" << sizeof(VC)
              << " sizeof(VE)=" << sizeof(VE) << " (each = one vtable pointer + its own fields)\n";
    std::cout << "switch  charge() x" << N << " : " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms\n";
    std::cout << "virtual charge() x" << N << " : " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms\n";
    std::cout << (s1 == s2 ? "identical totals\n" : "totals differ (different demo constants)\n");
}
