#include <iostream>
#include <string>
using namespace std;
class Event {
    string name; int rows,seats; char** seatMap;
public:
    Event(const string& n,int r,int s) : name(n),rows(r>0?r:0),seats(s>0?s:0),
        seatMap(rows>0?new char*[rows]:nullptr) {
        for(int i=0;i<rows;++i) { seatMap[i]=seats>0?new char[seats]:nullptr;
            for(int j=0;j<seats;++j) seatMap[i][j]='O'; }
        cout << "Created " << name << '\n';
    }
    void book(int r,int s) {
        if(r>=0&&r<rows&&s>=0&&s<seats&&seatMap[r][s]=='O') {
            seatMap[r][s]='X'; cout << "Booked (" << r << ',' << s << ")\n";
        } else cout << "Booking unavailable\n";
    }
    void cancel(int r,int s) {
        if(r>=0&&r<rows&&s>=0&&s<seats&&seatMap[r][s]=='X') {
            seatMap[r][s]='O'; cout << "Cancelled (" << r << ',' << s << ")\n";
        } else cout << "No booking to cancel\n";
    }
    ~Event() { for(int i=0;i<rows;++i) delete[] seatMap[i]; delete[] seatMap;
        cout << "Closed " << name << " (" << rows << " rows)" << '\n'; }
};
int main() {
    Event stackEvent("Stack event",2,3); stackEvent.book(0,1); stackEvent.cancel(0,1);
    { Event blockEvent("Block event",1,2); }
    Event* heapEvent=new Event("Heap event",1,1); delete heapEvent;
}
