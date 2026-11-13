// Tasks 5.1 and 5.2 - four ways to reach an object, this pointer, method chaining, array of pointers
#include <iomanip>
#include <iostream>
#include <string>

class Cart {
    std::string owner;
    std::string items[10];
    double      prices[10] = {};
    int         n = 0;
    double      discount = 0;                       // percent
public:
    explicit Cart(const std::string& owner = "guest") : owner(owner) {}

    Cart& add(const std::string& item, double price)          // returns *this -> chaining
    {
        if (n < 10) { items[n] = item; prices[n] = price; ++n; }
        return *this;
    }
    Cart& setDiscount(double discount)                        // member and parameter share a name
    {
        this->discount = discount;                            // this-> picks the member
        return *this;
    }
    double total() const
    {
        double t = 0;
        for (int i = 0; i < n; ++i) t += prices[i];
        return t * (100 - discount) / 100;
    }
    const std::string& getOwner() const { return owner; }
    const Cart* self() const { return this; }                 // 'this' is a pointer to the current object
};

void viaReference(Cart& r) { r.add("Milk", 30); }             // (c) reference parameter

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    Cart a("Asha");                                           // (a) directly by name
    a.add("Rice", 60).add("Dal", 120).setDiscount(10);
    std::cout << "(a) by name   : " << a.getOwner() << "  total = " << a.total() << '\n';

    Cart b("Bala");
    Cart* pb = &b;                                            // (b) through a pointer, ->
    pb->add("Oil", 180).add("Salt", 20);
    std::cout << "(b) by pointer: " << pb->getOwner() << "  total = " << pb->total() << '\n';

    Cart c("Charu");
    Cart& rc = c;                                             // (c) through a reference
    rc.add("Tea", 90);
    viaReference(c);
    std::cout << "(c) reference : " << rc.getOwner() << "  total = " << rc.total() << '\n';

    Cart* pd = new Cart("Dinesh");                            // (d) heap object: new ... delete
    pd->add("Sugar", 45).setDiscount(5);
    std::cout << "(d) new/delete: " << pd->getOwner() << "  total = " << pd->total() << '\n';
    std::cout << "this == &object ? " << (pd->self() == pd ? "yes" : "no") << '\n';
    delete pd;
    pd = nullptr;                                             // avoid a dangling pointer

    // ---- Task 5.2: array of pointers to the carts of all active customers ----
    Cart* active[4] = { &a, &b, &c, new Cart("Esha") };
    active[3]->add("Ghee", 650);
    Cart** best = active;                                     // pointer to the first element
    for (Cart** p = active + 1; p != active + 4; ++p)         // pointer arithmetic
        if ((*p)->total() > (*best)->total()) best = p;
    std::cout << "highest total: " << (*best)->getOwner() << " = " << (*best)->total()
              << " (index " << (best - active) << ")\n";
    delete active[3];                                         // only the heap one is released
}
