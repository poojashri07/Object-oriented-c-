#include <iostream>
#include <string>

class BusTicket {
    static int issued;                       // shared by all BusTicket objects
    static const int CAPACITY = 3;
    int seat;
    std::string name;
public:
    explicit BusTicket(const std::string& n) : seat(0), name(n)
    {
        if (issued < CAPACITY)               // TODO 1
            seat = ++issued;                 // seat stays 0 (waiting list) otherwise
    }
    static int count()
    {
        return issued;                       // TODO 2
    }
    void print() const
    {
        std::cout << name << ": "
                  << (seat ? "Seat " + std::to_string(seat) : std::string("Waiting")) << '\n';
    }
};
int BusTicket::issued = 0;                   // definition of the static data member

void bookTwo(const std::string& a, const std::string& b)
{ BusTicket x(a), y(b); x.print(); y.print(); }
int main()
{
    bookTwo("P", "Q");
    std::cout << "Issued after call 1: " << BusTicket::count() << '\n';
    bookTwo("R", "S");
    std::cout << "Issued after call 2: " << BusTicket::count() << '\n';
}
