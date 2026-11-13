// Task 1.2 - Repaired design: one base class, protected/private data, overridden pay()
#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Staff {                                   // abstract base: common data written ONCE
    std::string name_;
    int         id_;
public:
    Staff(const std::string& name, int id) : name_(name), id_(id) {}
    virtual ~Staff() = default;
    virtual double      pay()  const = 0;       // each category supplies its own rule
    virtual std::string role() const = 0;
    const std::string& name() const { return name_; }
    int                id()   const { return id_; }
};

class PermanentStaff : public Staff {           // shared rule: basic + DA
protected:
    static constexpr double DA_RATE = 0.42;     // named constant replaces magic number 0.42
    double basic_;
    double basicPlusDA() const { return basic_ + basic_ * DA_RATE; }
public:
    PermanentStaff(const std::string& n, int id, double basic) : Staff(n, id), basic_(basic) {}
};

class Professor : public PermanentStaff {
    double research_;
public:
    Professor(const std::string& n, int id, double basic, double research)
        : PermanentStaff(n, id, basic), research_(research) {}
    double      pay()  const override { return basicPlusDA() + research_; }
    std::string role() const override { return "Professor"; }
};

class LabAssistant : public PermanentStaff {
public:
    LabAssistant(const std::string& n, int id, double basic) : PermanentStaff(n, id, basic) {}
    double      pay()  const override { return basicPlusDA(); }
    std::string role() const override { return "LabAssistant"; }
};

class GuestFaculty : public Staff {
    double hours_, rate_;
public:
    GuestFaculty(const std::string& n, int id, double hours, double rate)
        : Staff(n, id), hours_(hours), rate_(rate) {}
    double      pay()  const override { return hours_ * rate_; }
    std::string role() const override { return "GuestFaculty"; }
};

int main()
{
    std::vector<std::unique_ptr<Staff>> staff;  // ONE container, ONE loop for all categories
    staff.push_back(std::make_unique<Professor>("Dr. Meena", 101, 80000, 5000));
    staff.push_back(std::make_unique<LabAssistant>("Ravi", 102, 30000));
    staff.push_back(std::make_unique<GuestFaculty>("Anita", 201, 40, 1500));

    std::cout << std::fixed << std::setprecision(2);
    double total = 0;
    for (const auto& s : staff) {
        std::cout << std::left << std::setw(14) << s->role() << std::setw(10) << s->name()
                  << std::right << std::setw(4) << s->id() << std::setw(12) << s->pay() << '\n';
        total += s->pay();
    }
    std::cout << "Total payroll: " << total << '\n';
}
