#include <iostream>

/*

div2 -> liczba podziałów
h    -> liczba pozostała
wynik = div2 + h

           |  div2 mod2 max sum        res  div2+sum   diff     h
           |                                                        
0          |  0    0    0   0          0    0          0        0
5          |  0    1    5   5          5    5          0        5
0 0 0      |  1    1    0   0          2    1          1        1
1 1        |  1    0    1   2          3    3          0        2
1 1 1 1    |  2    0    1   4          7    6          1        5
1 0 1 0    |  2    0    1   2          5    4          1        3
1 0 0 1    |  2    0    1   2          5    4          1        3
1 1 0 0 1  |  2    1    1   3          7    5          2        5

*/

int main(void)
{
    int z; std::cin >> z;
    while (z--) {
        int n; std::cin >> n;

        int m = n / 2;
        int x = n > 1 ? n % 2 : 0;
        int h = 0;
        while (n--) {
            int k; std::cin >> k;
            h += k;
        }

        std::cout << m + h + (m/2 + x) << '\n';
    }
    return 0;
}
