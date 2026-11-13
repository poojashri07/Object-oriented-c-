// Alternative: std::vector<Cart> (objects stored by value) instead of an array of pointers to Cart.
#include <chrono>
#include <iostream>
#include <string>
#include <vector>

struct Cart {
    std::string items[10]; double prices[10] = {}; int n = 0; double discount = 0;
    Cart& add(const std::string& i, double p) { if (n < 10) { items[n] = i; prices[n++] = p; } return *this; }
    double total() const { double t = 0; for (int i = 0; i < n; ++i) t += prices[i]; return t * (100 - discount) / 100; }
};

int main()
{
    // (1) pointer invalidation when the vector grows (we only COMPARE addresses; we never dereference the stale one)
    std::vector<Cart> v;
    v.reserve(2);
    v.emplace_back();
    const Cart* before = &v[0];
    std::cout << "capacity before = " << v.capacity() << ", &v[0] = " << static_cast<const void*>(before) << '\n';
    v.emplace_back(); v.emplace_back();                        // third element forces reallocation
    std::cout << "capacity after  = " << v.capacity() << ", &v[0] = " << static_cast<const void*>(&v[0]) << '\n';
    std::cout << (before == &v[0] ? "pointer still valid\n" : "pointer is now DANGLING (vector moved its elements)\n");

    // (2) sizes
    std::cout << "sizeof(Cart) = " << sizeof(Cart) << " bytes; sizeof(Cart*) = " << sizeof(Cart*) << " bytes\n";

    // (3) time to find the highest total, n = 200,000
    const int N = 200000;
    std::vector<Cart> objs(N);
    for (int i = 0; i < N; ++i) { objs[i].add("x", i % 1000); }
    std::vector<Cart*> scattered;
    for (int i = 0; i < N; ++i) { scattered.push_back(new Cart); scattered.back()->add("x", i % 1000); }

    using clk = std::chrono::steady_clock;
    auto t0 = clk::now();
    double best1 = 0; for (const auto& c : objs) if (c.total() > best1) best1 = c.total();
    auto t1 = clk::now();
    double best2 = 0; for (auto* c : scattered) if (c->total() > best2) best2 = c->total();
    auto t2 = clk::now();
    std::cout << "vector<Cart>   scan: " << std::chrono::duration<double, std::milli>(t1 - t0).count() << " ms (best " << best1 << ")\n";
    std::cout << "Cart* array    scan: " << std::chrono::duration<double, std::milli>(t2 - t1).count() << " ms (best " << best2 << ")\n";
    for (auto* c : scattered) delete c;
}
