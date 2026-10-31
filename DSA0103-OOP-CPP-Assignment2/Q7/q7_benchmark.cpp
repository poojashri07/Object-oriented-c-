#include <chrono>
#include <iostream>

template <int N> struct ShiftLog {
    double a[N]; int count = 0;
    void add(double t) {
        if (count == N) { for (int i = 1; i < N; ++i) a[i - 1] = a[i]; a[N - 1] = t; }
        else a[count++] = t;
    }
    double last() const { return a[count - 1]; }
};
template <int N> struct RingLog {
    double a[N]; int start = 0, count = 0;
    void add(double t) {
        a[(start + count) % N] = t;
        if (count < N) ++count; else start = (start + 1) % N;
    }
    double last() const { return a[(start + count - 1) % N]; }
};

template <class Log>
double run(long adds, double& sink)
{
    static Log log;                              // static: avoids a large stack object
    auto t0 = std::chrono::steady_clock::now();
    for (long i = 0; i < adds; ++i) { log.add(double(i)); sink += log.last(); }
    auto t1 = std::chrono::steady_clock::now();
    return std::chrono::duration<double, std::milli>(t1 - t0).count();
}
template <int N>
void compare(long adds)
{
    double s1 = 0, s2 = 0;
    double ts = run<ShiftLog<N>>(adds, s1);
    double tr = run<RingLog<N>>(adds, s2);
    std::cout << "N=" << N << "  shift " << ts << " ms  ring " << tr
              << " ms  (checksums " << s1 << ", " << s2 << ")\n";
}
int main()
{
    compare<10>(100000);
    compare<50>(100000);
    compare<1000>(100000);
    compare<10000>(100000);
}