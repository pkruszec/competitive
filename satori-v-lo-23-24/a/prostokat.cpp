#include <iostream>

int main(void) {
    int h, w;
    std::cin >> h >> w;
    h -= 2;

    for (int i = 0; i < w; ++i) std::cout << 'X';
    std::cout << '\n';

    for (int i = 0; i < h; ++i) {
        std::cout << 'X';
        for (int i = 0; i < w - 2; ++i) std::cout << ' ';
        std::cout << 'X';
        std::cout << '\n';
    }

    for (int i = 0; i < w; ++i) std::cout << 'X';
    std::cout << '\n';
}
