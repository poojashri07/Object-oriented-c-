#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;
class Book {
    string title, author; int copies;
    static int check(int n) { if (n < 0) throw invalid_argument("copies cannot be negative"); return n; }
public:
    Book() : Book("", "", 0) {}
    explicit Book(const string& t) : Book(t, "Unknown", 0) {}
    Book(const string& t, const string& a) : Book(t, a, 0) {}
    Book(const string& t, const string& a, int n) : title(t), author(a), copies(check(n)) {}
    void print() const { cout << "Title: " << title << ", Author: " << author << ", Copies: " << copies << '\n'; }
};
int main() {
    Book empty; Book donated("C++ Basics"); Book full("Object Oriented Programming", "B. Stroustrup", 5);
    empty.print(); donated.print(); full.print();
    try { Book bad("Invalid book", "Unknown", -1); }
    catch (const invalid_argument& e) { cout << "Error: " << e.what() << '\n'; }
}
