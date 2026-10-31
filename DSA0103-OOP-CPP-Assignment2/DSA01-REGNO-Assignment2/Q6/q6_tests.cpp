#include <iostream>
#include <cstdlib>
class Time { int h, m; public: Time(int hh,int mm):h(hh),m(mm){}
 friend int minutesBetween(const Time&, const Time&); friend bool earlier(const Time&, const Time&); };
int minutesBetween(const Time& a, const Time& b){ return std::abs((a.h*60+a.m)-(b.h*60+b.m)); }
bool earlier(const Time& a, const Time& b){ return a.h*60+a.m < b.h*60+b.m; }
void t(int h1,int m1,int h2,int m2){ Time a(h1,m1), b(h2,m2); std::cout << h1 << ":" << m1 << " , " << h2 << ":" << m2 << "  ->  " << minutesBetween(a,b) << "  " << std::boolalpha << earlier(a,b) << '\n'; }
int main(){ t(9,45,13,10); t(11,59,12,1); t(12,1,11,59); t(12,0,12,0); }
