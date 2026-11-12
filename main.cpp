#include <iostream>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>
using namespace std;
struct Counter {
    int value;
    Counter& operator++(){++value;return *this;}
    Counter operator++(int){Counter old=*this;++value;return old;}
};
class Playlist {
    vector<string> tracks;
public:
    explicit Playlist(vector<string> t):tracks(std::move(t)){}
    string& operator[](int i) {
        if(i<0||i>=static_cast<int>(tracks.size())) throw out_of_range("track index out of range");
        return tracks[i];
    }
    const string& operator[](int i) const {
        if(i<0||i>=static_cast<int>(tracks.size())) throw out_of_range("track index out of range");
        return tracks[i];
    }
};
int main() {
    Counter c{5}; Counter a=c++; Counter b=++c;
    cout << a.value << ' ' << b.value << ' ' << c.value << '\n';
    Playlist p({"Intro","Song A","Song B"}); cout << p[1] << '\n';
    try { cout << p[3] << '\n'; } catch(const out_of_range& e) { cout << e.what() << '\n'; }
}
