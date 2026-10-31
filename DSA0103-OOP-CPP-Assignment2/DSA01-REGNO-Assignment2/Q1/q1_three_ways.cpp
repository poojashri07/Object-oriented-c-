#include <iostream>

void concessionByValue(long long fee, int percent)
{
    fee -= fee * percent / 100;
    std::cout << "  inside (value)   : " << fee << '\n';
}
void concessionByRef(long long& fee, int percent)
{
    fee -= fee * percent / 100;
}
void concessionByPtr(long long* fee, int percent)
{
    if (fee) *fee -= *fee * percent / 100;   // guard against nullptr
}
long long concessionReturn(long long fee, int percent)   // used in Design Decision
{
    return fee - fee * percent / 100;
}

int main()
{
    long long f1 = 45000, f2 = 45000, f3 = 45000, f4 = 45000;
    concessionByValue(f1, 10);   std::cout << "by value  : " << f1 << '\n';
    concessionByRef(f2, 10);     std::cout << "by ref    : " << f2 << '\n';
    concessionByPtr(&f3, 10);    std::cout << "by pointer: " << f3 << '\n';
    f4 = concessionReturn(f4, 10); std::cout << "by return : " << f4 << '\n';
}