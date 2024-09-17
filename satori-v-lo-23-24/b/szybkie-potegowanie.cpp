#include <iostream>

static int ipow(int a, int n)
{
    int k = 1;
    while (n--) k *= a;
    return k;
}

static int f(int a, int k, int q)
{
    return (ipow(a%q, k) % q);
}

int main(void)
{
    int z;
    std::cin >> z;
    while (z--) {
        int a, k, q;
        std::cin >> a >> k >> q;

        std::cout << f(a, k, q) << '\n';
    }
    return 0;
}
