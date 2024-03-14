#include <iostream>

// int powers_of_2[31] = {
//     1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 
//     16384, 32768, 65536, 131072, 262144, 524288, 1048576, 2097152, 
//     4194304, 8388608, 16777216, 33554432, 67108864, 134217728, 
//     268435456, 536870912, 1073741824
// };

int biggest_power = 1073741823;

int powers_of_2[31] = {
    0, 1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 
    65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 
    33554431, 67108863, 134217727, 268435455, 536870911, 1073741823
};

// int fib[1000000];

/*
int fib_mod2(int s, int p)
{
    if (s < 2) return 1;
    int power = powers_of_2[p];

    return (fib_mod2(s - 2, p) % power + fib_mod2(s - 1, p) % power) % power;
}
*/

// %         56.803
// &         11.455
// -1 baked  11.635
// '\n'      11.506

/*
p = 2 (4)

*/

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int count = 0; // liczba przypadków testowych
    std::cin >> count;

    int max = 1000000;
    int *fib = new int[max];
    fib[0] = 1;
    int a = 0;
    int b = 1;

    for (int i = 1; i < max; ++i) {
        int t = a;
        a = b;
        b = (t+b) & biggest_power;
        fib[i] = b;
        // if (i < 10) std::cout << fib[i-1] << ",";
    }

    for (int i = 0;
         i < count;
         ++i)
    {
        int s = 0; // s-ta liczba w ciągu fibonacciego
        int p = 0; // wynik musi być podany modulo 2^p
        std::cin >> s >> p;

        std::cout << (fib[s] & powers_of_2[p]) << '\n';
/*
        int a = 0;
        int b = 1;

        int power = powers_of_2[p];// - 1;

        for (int j = 0; j < s; ++j) {
            int t = a;
            a = b;
            b = (t+b) & power;
        }

        std::cout << b << '\n';

*/
    }

    return 0;
}