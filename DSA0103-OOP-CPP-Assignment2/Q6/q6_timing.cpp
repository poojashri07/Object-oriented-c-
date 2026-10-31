#include <chrono>
#include <cstdlib>
#include <iostream>

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int  minutesInline(const Time&, const Time&);
    friend int  minutesNoInline(const Time&, const Time&);
};
inline int minutesInline(const Time& a, const Time& b)
{ return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m)); }

__attribute__((noinline))                   // GCC/Clang: forbids inlining
int minutesNoInline(const Time& a, const Time& b)
{ return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m)); }

template <typename F>
double timeIt(F f, long long& sink)
{
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000000; ++i) {
        Time a(i % 24, i % 60), b((i / 7) % 24, (i / 3) % 60);   // varying data, no constant folding
        sink += f(a, b);
    }
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
int main()
{
    long long s1 = 0, s2 = 0;
    double t1 = timeIt([](const Time& a, const Time& b){ return minutesInline(a, b); },   s1);
    double t2 = timeIt([](const Time& a, const Time& b){ return minutesNoInline(a, b); }, s2);
    std::cout << "inline    : " << t1 << " ms  (checksum " << s1 << ")\n";
    std::cout << "no inline : " << t2 << " ms  (checksum " << s2 << ")\n";
}