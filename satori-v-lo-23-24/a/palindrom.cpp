#include <iostream>

int main(void)
{
    int z; std::cin >> z;
    char *s = new char[100000];
    while (z--) {
        int n;
        std::cin >> n;
        for (int i = 0; i < n; ++i) std::cin >> s[i];

        bool is = true;
        int k = n / 2;
        for (int i = 0; i < k; ++i) {
            char a = s[i];
            char b = s[n-i-1];
            if (a != b) {
                is = false;
                break;
            }
        }

        if (is) {
            std::cout << "TAK\n";
        } else {
            std::cout << "NIE\n";
        }
    }

    return 0;
}