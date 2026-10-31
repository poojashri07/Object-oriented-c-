#include <iostream>
double charge(double weight) { return weight * 40; }
double charge(double weight, bool express) { return weight * 40 + (express ? 30 : 0); }
double charge(double weight, bool express = false, bool insured = false) { return weight * 40 + (express ? 30 : 0) + (insured ? 20 : 0); }
int main() { std::cout << charge(2.5) << '\n'; std::cout << charge(2.5, true) << '\n'; }
