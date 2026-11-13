#include <cmath>
#include <iostream>
#include <stdexcept>
using namespace std;
class Complex {
    double real,imag;
public:
    Complex():real(0),imag(0){}
    Complex(double r):real(r),imag(0){}
    Complex(double r,double i):real(r),imag(i){}
    Complex operator+(const Complex& z)const{return Complex(real+z.real,imag+z.imag);}
    Complex operator-(const Complex& z)const{return Complex(real-z.real,imag-z.imag);}
    Complex operator*(const Complex& z)const{return Complex(real*z.real-imag*z.imag,real*z.imag+imag*z.real);}
    Complex operator/(const Complex& z)const{
        double d=z.real*z.real+z.imag*z.imag;
        if(d==0)throw domain_error("division by zero impedance");
        return Complex((real*z.real+imag*z.imag)/d,(imag*z.real-real*z.imag)/d);
    }
    bool operator==(const Complex& z)const{return real==z.real&&imag==z.imag;}
    double magnitude()const{return sqrt(real*real+imag*imag);}
    friend ostream& operator<<(ostream& out,const Complex& z){
        out<<z.real;if(z.imag>=0)out<<" + j"<<z.imag;else out<<" - j"<<-z.imag;return out;
    }
};
int main(){
    Complex r(10,0),l(0,5),c(0,-2);Complex series=r+l+c;
    Complex parallel=(r*l)/(r+l);
    cout<<"Series impedance: "<<series<<'\n';
    cout<<"Magnitude: "<<series.magnitude()<<'\n';
    cout<<"Parallel impedance: "<<parallel<<'\n';
    try{Complex zero;cout<<r/zero<<'\n';}
    catch(const domain_error& e){cout<<"Error: "<<e.what()<<'\n';}
}
