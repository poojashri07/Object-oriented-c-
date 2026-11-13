#include <iomanip>
#include <iostream>
using namespace std;
class Money {
    long long paise;
public:
    Money(long long rupees=0,int p=0):paise(rupees*100+p){}
    Money operator+(const Money& o) const { Money r; r.paise=paise+o.paise; return r; }
    bool operator==(const Money& o) const { return paise==o.paise; }
    friend ostream& operator<<(ostream& out,const Money& m) {
        long long rupees=m.paise/100, p=m.paise%100; if(p<0)p=-p;
        out << "Rs " << rupees << '.' << setw(2) << setfill('0') << p; return out;
    }
};
int main() {
    Money a(120,75),b(79,25); Money total=a+b;
    cout << total << '\n' << boolalpha << (total==Money(200)) << '\n';
    cout << Money(0,75)+Money(0,50) << '\n';
}
