// Stage 5 - extension demo: ElectricBus is added; fleet.h is untouched.
#include "electric_bus.h"

int main()
{
    Fleet fleet(Date(13, 11, 2026));
    fleet.add(new Car("CR-201", 1800, 20.0, Date(1, 2, 2027), 5));
    fleet.add(new ElectricBus("EB-401", 9000, 200.0, Date(1, 8, 2027), 32, 250.0));   // NEW TYPE
    fleet.list();
    fleet.rent("EB-401", 2);
    fleet.giveBack("EB-401", 3, 90.0);          // 1 day late, 90 kWh -> uses ElectricBus::charge via the same Fleet code
    fleet.rent("CR-201", 1);
    fleet.giveBack("CR-201", 1, 6.0);
    fleet.list();
}
