// fleet.h - Vehicle Rental Fleet : abstract base, derived classes, member class Date, Fleet manager.
// This header is NEVER edited when a new vehicle type is added (Open/Closed principle).
#pragma once
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

// ---------- member class (has-a) : calendar date used for service due ----------
class Date {
    int d_, m_, y_;
public:
    Date(int d = 1, int m = 1, int y = 2026) : d_(d), m_(m), y_(y) {}
    int key() const { return y_ * 10000 + m_ * 100 + d_; }            // comparable form YYYYMMDD
    bool before(const Date& o) const { return key() < o.key(); }
    std::string str() const {
        std::ostringstream os;
        os << std::setfill('0') << std::setw(2) << d_ << '-' << std::setw(2) << m_ << '-' << y_;
        return os.str();
    }
};

// ---------- abstract base class ----------
class Vehicle {
    std::string regNo_;
    double      dailyRate_;
    bool        rented_ = false;
    int         plannedDays_ = 0;
protected:
    double dailyRate() const { return dailyRate_; }
public:
    Vehicle(const std::string& reg, double rate) : regNo_(reg), dailyRate_(rate) {}
    Vehicle(const Vehicle&) = delete;                  // polymorphic base: no copying -> no slicing
    Vehicle& operator=(const Vehicle&) = delete;
    virtual ~Vehicle() = default;

    // ---- pure virtual: the behaviour that DIFFERS between vehicle types ----
    virtual double      charge(int plannedDays, int lateDays, double energyUsed) const = 0;
    virtual std::string type() const = 0;

    // ---- virtual with a default: derived classes extend it ----
    virtual bool isAvailable(const Date&) const { return !rented_; }
    virtual void describe(std::ostream& os) const { os << type() << " " << regNo_ << " @Rs." << dailyRate_ << "/day"; }

    // ---- common behaviour written ONCE ----
    const std::string& regNo() const { return regNo_; }
    bool  isRented()    const { return rented_; }
    int   plannedDays() const { return plannedDays_; }
    void  markRented(int days) { rented_ = true; plannedDays_ = days; }
    void  markReturned()       { rented_ = false; plannedDays_ = 0; }
};

// ---------- Bicycle ----------
class Bicycle : public Vehicle {
public:
    Bicycle(const std::string& reg, double rate) : Vehicle(reg, rate) {}
    double charge(int planned, int late, double) const override { return dailyRate() * planned + dailyRate() * 1.5 * late; }
    std::string type() const override { return "Bicycle"; }
};

// ---------- MotorVehicle : still abstract (charge() not yet implemented) ----------
class MotorVehicle : public Vehicle {
    double energyLevel_;            // litres of fuel or kWh of charge
    Date   serviceDue_;             // member class (has-a)
public:
    MotorVehicle(const std::string& reg, double rate, double level, const Date& due)
        : Vehicle(reg, rate), energyLevel_(level), serviceDue_(due) {}
    bool isAvailable(const Date& today) const override {          // overdue service blocks renting
        return Vehicle::isAvailable(today) && !serviceDue_.before(today);
    }
    void describe(std::ostream& os) const override {
        Vehicle::describe(os);
        os << ", level " << energyLevel_ << ", service due " << serviceDue_.str();
    }
protected:
    double baseCharge(int planned, int late, double lateMultiplier) const {
        return dailyRate() * planned + dailyRate() * lateMultiplier * late;
    }
};

// ---------- TwoWheeler : fuel charged per litre ----------
class TwoWheeler : public MotorVehicle {
    static constexpr double PER_LITRE = 105.0;
public:
    using MotorVehicle::MotorVehicle;
    double charge(int planned, int late, double litres) const override { return baseCharge(planned, late, 2.0) + litres * PER_LITRE; }
    std::string type() const override { return "TwoWheeler"; }
};

// ---------- Car : seating capacity, fuel charged per litre ----------
class Car : public MotorVehicle {
    int seats_;
    static constexpr double PER_LITRE = 105.0;
public:
    Car(const std::string& reg, double rate, double fuel, const Date& due, int seats)
        : MotorVehicle(reg, rate, fuel, due), seats_(seats) {}
    double charge(int planned, int late, double litres) const override { return baseCharge(planned, late, 2.0) + litres * PER_LITRE; }
    std::string type() const override { return "Car"; }
    void describe(std::ostream& os) const override { MotorVehicle::describe(os); os << ", seats " << seats_; }
protected:
    int seats() const { return seats_; }
};

// ---------- ElectricCar : battery capacity, charged per kWh (multilevel: Vehicle>MotorVehicle>Car>ElectricCar) ----------
class ElectricCar : public Car {
    double batteryKWh_;
    static constexpr double PER_KWH = 9.0;
public:
    ElectricCar(const std::string& reg, double rate, double charge, const Date& due, int seats, double battery)
        : Car(reg, rate, charge, due, seats), batteryKWh_(battery) {}
    double charge(int planned, int late, double kWh) const override { return baseCharge(planned, late, 2.0) + kWh * PER_KWH; }
    std::string type() const override { return "ElectricCar"; }
    void describe(std::ostream& os) const override { Car::describe(os); os << ", battery " << batteryKWh_ << " kWh"; }
};

// ---------- Fleet : array of base-class pointers ----------
class Fleet {
    static constexpr int MAX = 20;
    Vehicle* v_[MAX] = {};
    int      n_ = 0;
    Date     today_;
    Vehicle* find(const std::string& reg) const {
        for (int i = 0; i < n_; ++i) if (v_[i]->regNo() == reg) return v_[i];
        return nullptr;
    }
public:
    explicit Fleet(const Date& today) : today_(today) { std::cout << std::fixed << std::setprecision(2); }
    Fleet(const Fleet&) = delete;
    Fleet& operator=(const Fleet&) = delete;
    ~Fleet() { for (int i = 0; i < n_; ++i) delete v_[i]; }     // virtual destructors make this safe

    bool add(Vehicle* v) { if (n_ == MAX) { delete v; return false; } v_[n_++] = v; return true; }

    bool rent(const std::string& reg, int days) {
        Vehicle* v = find(reg);
        if (!v)                       { std::cout << "  [rent] " << reg << ": not found\n"; return false; }
        if (!v->isAvailable(today_))  { std::cout << "  [rent] " << reg << ": NOT available (rented or service overdue)\n"; return false; }
        v->markRented(days);
        std::cout << "  [rent] " << v->type() << " " << reg << " rented for " << days << " day(s)\n";
        return true;
    }
    double giveBack(const std::string& reg, int daysUsed, double energyUsed) {
        Vehicle* v = find(reg);
        if (!v || !v->isRented())     { std::cout << "  [return] " << reg << ": not currently rented\n"; return -1; }
        int late = daysUsed > v->plannedDays() ? daysUsed - v->plannedDays() : 0;
        double amt = v->charge(v->plannedDays(), late, energyUsed);   // run-time dispatch
        std::cout << "  [return] " << v->type() << " " << reg << ": planned " << v->plannedDays()
                  << ", used " << daysUsed << ", late " << late << " -> Rs." << std::fixed << std::setprecision(2) << amt << '\n';
        v->markReturned();
        return amt;
    }
    void list() const {
        std::cout << "  ---- fleet (" << n_ << " vehicles, today " << today_.str() << ") ----\n";
        for (int i = 0; i < n_; ++i) {
            std::cout << "  " << (v_[i]->isRented() ? "[RENTED] " : (v_[i]->isAvailable(today_) ? "[free]   " : "[BLOCKED]"));
            std::cout << ' ';  v_[i]->describe(std::cout);  std::cout << '\n';
        }
    }
};
