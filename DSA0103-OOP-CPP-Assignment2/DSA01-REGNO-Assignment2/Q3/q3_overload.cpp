#include <iostream>
struct Parcel { double kg; bool express; bool insured; };
double charge(int grams);
double charge(double kg, bool express = false, bool insured = false);
double charge(const Parcel& p);
double charge(int grams) { std::cout << "[int grams] "; return charge(grams / 1000.0); }
double charge(double kg, bool express, bool insured)
{ std::cout << "[double kg] "; double c = kg * 40.0; if (express) c += 30.0; if (insured) c += 20.0; return c; }
double charge(const Parcel& p) { std::cout << "[Parcel] "; return charge(p.kg, p.express, p.insured); }
int main()
{
    std::cout << "charge(2500)            : "; std::cout << charge(2500) << '\n';
    std::cout << "charge(2.5)             : "; std::cout << charge(2.5) << '\n';
    std::cout << "charge(2.5, true)       : "; std::cout << charge(2.5, true) << '\n';
    std::cout << "charge(2.5, true, true) : "; std::cout << charge(2.5, true, true) << '\n';
    std::cout << "charge(2)               : "; std::cout << charge(2) << '\n';
    std::cout << "charge(2.0f)            : "; std::cout << charge(2.0f) << '\n';
    std::cout << "charge(Parcel)          : "; std::cout << charge(Parcel{2.5, true, false}) << '\n';
}
