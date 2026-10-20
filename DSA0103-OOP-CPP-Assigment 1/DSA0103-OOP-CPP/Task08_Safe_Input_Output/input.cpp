#include <iostream>
#include <limits>
int main() {
    int hour;
    while (true) {
        std::cout << "Enter hour (0-23): ";
        if (std::cin >> hour) {
            if (hour >= 0 && hour <= 23) break;
            std::cout << "Hour must be from 0 to 23.\n";
        } else {
            if (std::cin.eof()) return 1;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Enter a number.\n";
        }
    }
    std::cout << "Accepted hour = " << hour << '\n';
}
