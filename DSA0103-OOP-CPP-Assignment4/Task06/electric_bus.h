// electric_bus.h - NEW vehicle type added WITHOUT editing fleet.h or any existing class.
#pragma once
#include "fleet.h"

class ElectricBus : public MotorVehicle {
    int    seats_;
    double batteryKWh_;
    static constexpr double PER_KWH = 8.5;
public:
    ElectricBus(const std::string& reg, double rate, double charge, const Date& due, int seats, double battery)
        : MotorVehicle(reg, rate, charge, due), seats_(seats), batteryKWh_(battery) {}
    double charge(int planned, int late, double kWh) const override { return baseCharge(planned, late, 3.0) + kWh * PER_KWH; }
    std::string type() const override { return "ElectricBus"; }
    void describe(std::ostream& os) const override {
        MotorVehicle::describe(os);
        os << ", seats " << seats_ << ", battery " << batteryKWh_ << " kWh";
    }
};
