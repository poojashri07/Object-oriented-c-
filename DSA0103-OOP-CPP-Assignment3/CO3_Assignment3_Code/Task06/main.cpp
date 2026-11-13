#include <cstring>
#include <iostream>
using namespace std;
class Text {
    char* data;
public:
    Text(const char* s=""){data=new char[strlen(s)+1];strcpy(data,s);}
    Text(const Text& o){data=new char[strlen(o.data)+1];strcpy(data,o.data);}
    Text& operator=(const Text& o) {
        if(this!=&o){char* fresh=new char[strlen(o.data)+1];strcpy(fresh,o.data);delete[] data;data=fresh;}
        return *this;
    }
    ~Text(){delete[] data;}
    Text operator+(const Text& o) const {
        char* joined=new char[strlen(data)+strlen(o.data)+1];strcpy(joined,data);strcat(joined,o.data);
        Text result(joined);delete[] joined;return result;
    }
    bool operator==(const Text& o) const{return strcmp(data,o.data)==0;}
    bool operator!=(const Text& o) const{return !(*this==o);}
    friend ostream& operator<<(ostream& out,const Text& t){return out<<t.data;}
};
int main(){
    Text a("Hello "),b("World");Text c=a+b;
    cout<<c<<'\n'<<boolalpha<<(c!=a)<<'\n';c=c;
    Text empty;cout<<'['<<empty<<']'<<'\n';
}
