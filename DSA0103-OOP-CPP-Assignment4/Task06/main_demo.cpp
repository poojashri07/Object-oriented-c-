// Stage 5 - demonstrate renting each type and returning with a late charge
#include "fleet.h"

int main()
{
    Fleet fleet(Date(13, 11, 2026));
    fleet.add(new Bicycle("BI-001", 150));
    fleet.add(new TwoWheeler("TW-101", 400, 5.0, Date(1, 3, 2027)));
    fleet.add(new Car("CR-201", 1800, 20.0, Date(1, 2, 2027), 5));
    fleet.add(new ElectricCar("EV-301", 2500, 40.0, Date(1, 6, 2027), 5, 40.0));
    fleet.add(new Car("CR-202", 1800, 15.0, Date(1, 10, 2026), 4));      // service date already passed

    std::cout << "== initial fleet ==\n";  fleet.list();

    std::cout << "\n== renting each type ==\n";
    fleet.rent("BI-001", 2);
    fleet.rent("TW-101", 3);
    fleet.rent("CR-201", 4);
    fleet.rent("EV-301", 2);
    fleet.rent("CR-202", 1);        // must be refused: service overdue
    fleet.rent("BI-001", 1);        // must be refused: already rented
    fleet.rent("XX-999", 1);        // must be refused: unknown registration

    std::cout << "\n== fleet after renting ==\n";  fleet.list();

    std::cout << "\n== returns (second argument = days actually used, third = litres or kWh consumed) ==\n";
    fleet.giveBack("BI-001", 2, 0);       // on time
    fleet.giveBack("TW-101", 5, 4.0);     // 2 days late, 4 litres
    fleet.giveBack("CR-201", 4, 12.5);    // on time, 12.5 litres
    fleet.giveBack("EV-301", 3, 18.0);    // 1 day late, 18 kWh
    fleet.giveBack("EV-301", 1, 0);       // already returned

    std::cout << "\n== final fleet ==\n";  fleet.list();
}
