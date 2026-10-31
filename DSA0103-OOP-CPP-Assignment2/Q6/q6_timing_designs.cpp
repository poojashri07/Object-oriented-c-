#include <chrono>
#include <cstdlib>
#include <iostream>
class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int minutesFriend(const Time&, const Time&);
    int minutesTo(const Time& o) const { return std::abs((o.h*60+o.m) - (h*60+m)); }
    int hour() const { return h; }
    int minute() const { return m; }
};
int minutesFriend(const Time& a, const Time& b) { return std::abs((a.h*60+a.m) - (b.h*60+b.m)); }
int minutesGetter(const Time& a, const Time& b) { return std::abs((a.hour()*60+a.minute()) - (b.hour()*60+b.minute())); }
template <typename F> double timeIt(F f, long long& sink) {
    auto t0 = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000000; ++i) { Time a(i % 24, i % 60), b((i/7) % 24, (i/3) % 60); sink += f(a, b); }
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
int main() {
    long long s1=0,s2=0,s3=0;
    double a = timeIt([](const Time& x,const Time& y){ return minutesFriend(x,y); }, s1);
    double b = timeIt([](const Time& x,const Time& y){ return x.minutesTo(y); }, s2);
    double c = timeIt([](const Time& x,const Time& y){ return minutesGetter(x,y); }, s3);
    std::cout << a << " " << b << " " << c << " " << (s1==s2 && s2==s3) << '\n';
}
