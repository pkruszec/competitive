#include <iostream>

int main(void)
{
    int z;
    std::cin >> z;
    while (z--) {
        int a, b;
        std::cin >> a >> b;
        while (b != 0) {
            int c = a % b;
            a = b;
            b = c;
        }
        std::cout << a << '\n';
    }
    return 0;
}
