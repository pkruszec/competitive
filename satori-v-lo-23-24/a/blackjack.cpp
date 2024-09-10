#include <iostream>

int main(void) {
    int a, b;
    std::cin >> a >> b;
    if (a + b == 21) {
        std::cout << "Blackjack!\n";
    } else {
        std::cout << a + b;
    }
    return 0;
}
