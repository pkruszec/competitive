#include <iostream>
#include <string>
#include <ctype.h>

int main(void) {
    int z;
    std::cin >> z;
    std::string s;
    for (int i = 0; i < z; ++i) {
        s.clear();
        std::cin >> s;
        if (isdigit(s[0])) {
            int x = std::stoi(s);
            
            auto f = [&](int k, const char *s){
                while (x >= k) {
                    std::cout << s;
                    x -= k;
                }
            };

            f(1000, "M");
            f(900,  "CM");
            f(500,  "D");
            f(400,  "CD");
            f(100,  "C");
            f(90,   "XC");
            f(50,   "L");
            f(40,   "XL");
            f(10,   "X");
            f(9,    "IX");
            f(5,    "V");
            f(4,    "IV");
            f(1,    "I");
            std::cout << '\n';
        } else {
            int x = 0;
            int p = 0;

            auto f = [&](int k, const char *g) {
                int p1 = p;
                while (*g) {
                    if (*g != s[p1]) return;
                    p1++;
                    g++;
                }

                p = p1;
                x += k;
            };

            while (p < s.size()) {
                f(1000, "M");
                f(900,  "CM");
                f(500,  "D");
                f(400,  "CD");
                f(100,  "C");
                f(90,   "XC");
                f(50,   "L");
                f(40,   "XL");
                f(10,   "X");
                f(9,    "IX");
                f(5,    "V");
                f(4,    "IV");
                f(1,    "I");
            }

            std::cout << x << '\n';
        }
    }
    return 0;
}
