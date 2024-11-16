#include <cmath>
#include "kaslib.h"

long long primes[] = {
    236597890729009,
    13007707,
};

bool is_interesting(long long x, long long thr)
{
    if (x < thr) {
        return false;
    }

    return true;
}

long long func(long long t)
{
    return 5 + t*t + t*t*t;
}

int main()
{   
    #ifdef HOME
    long long seed;
    cin >> seed;
    rng = mt19937_64(seed);
    #endif

    long long n = DajN();
    long long start = n;
    long long stop = 0;

    while (true) {
        long long t = 0;

        long long guess = 0;
        for (long long i = start; i >= stop;) {
            long long result = Pytaj(i);

            long long x = func(t);
            if (!is_interesting(result, x)) {
                goto next;
            }

            if (result == i) {
                guess = result;
                break;
            }

            i -= result;
            t++;
        }

        if (!guess) {
            goto next;
        }

        Odpowiedz(guess);

        next:;
        Szturchnij();
    }

    return 0;
}
