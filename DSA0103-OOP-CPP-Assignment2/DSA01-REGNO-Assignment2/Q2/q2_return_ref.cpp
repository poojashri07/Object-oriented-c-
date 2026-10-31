#include <iostream>
#include <vector>

int& highest(int marks[], int n)              // returns alias to the element
{
    int idx = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[idx]) idx = i;
    return marks[idx];
}
const int& highestConstRef(const int marks[], int n)   // read-only alias
{
    int idx = 0;
    for (int i = 1; i < n; ++i)
        if (marks[i] > marks[idx]) idx = i;
    return marks[idx];
}
int highestCopy(const int marks[], int n)     // returns a copy
{
    return highestConstRef(marks, n);
}
int& dangling()                               // BUG ON PURPOSE
{
    int local = 99;
    return local;                             // warning: reference to local variable returned
}
int main()
{
    int marks[5] = {56, 78, 91, 67, 85};
    highest(marks, 5) += 2;                   // moderation applied directly
    highest(marks, 5) = highest(marks, 5) + 1; // call on the left of =
    std::cout << "marks[2] = " << marks[2] << '\n';

    int c = highestCopy(marks, 5);            // copy: changing c does not change the array
    c = 0;
    std::cout << "after changing copy, marks[2] = " << marks[2] << '\n';
    // highestConstRef(marks, 5) += 2;        // would not compile: const

    // Changed condition: growing vector
    std::vector<int> v{56, 78, 91};
    int* before = &v[2];
    v.push_back(70);                          // may reallocate
    std::cout << "address changed after push_back? "
              << (before != &v[2] ? "yes" : "no") << '\n';
    // Do NOT read *before here: it may be a dangling pointer.
}