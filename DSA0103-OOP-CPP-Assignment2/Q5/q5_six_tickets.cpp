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

int main()
{
    BusTicket t[6] = {BusTicket("A"), BusTicket("B"), BusTicket("C"), BusTicket("D"), BusTicket("E"), BusTicket("F")};
    for (const BusTicket& x : t) x.print();
    std::cout << "Issued: " << BusTicket::count() << '\n';
}
