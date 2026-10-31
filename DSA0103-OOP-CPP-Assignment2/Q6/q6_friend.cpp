#include <iostream>
#include <cstdlib>      // std::abs

class Time {
    int h, m;
public:
    Time(int hh, int mm) : h(hh), m(mm) {}
    friend int  minutesBetween(const Time& a, const Time& b);
    friend bool earlier(const Time& a, const Time& b);
};

int minutesBetween(const Time& a, const Time& b)
{
    return std::abs((a.h * 60 + a.m) - (b.h * 60 + b.m));   // TODO 1
}
bool earlier(const Time& a, const Time& b)
{
    return a.h * 60 + a.m < b.h * 60 + b.m;                 // TODO 2
}

int main()
{
    Time departure(9, 45), arrival(13, 10);
    std::cout << minutesBetween(departure, arrival) << ' '
              << std::boolalpha << earlier(arrival, departure) << '\n';
}