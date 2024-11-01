#include "kaslib.h"

int main()
{   
    #ifdef HOME
    long long seed;
    cin >> seed;
    rng = mt19937_64(seed);
    #endif

    /*
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    */
   
    long long n = DajN();
    long long start = n;
    long long stop = 0;
    long long threshold = 5000;
    long long min_result = 5000;
    // long long threshold = 7500;
    // long long threshold = 15000;

    while (true) {  
        long long count = 0;
        long long guess = 0;
        for (long long i = start; i >= stop;) {
            // cout << DajX() << " -> " << i << "\n";

            if (count > threshold) {
                Szturchnij();
                goto next;
            }

            long long result = Pytaj(i);

            if (result < min_result) {
                Szturchnij();
                goto next;
            }

            if (result == i) {
                guess = result;
                break;
            }

            i -= result;
            count++;
        }

        if (!guess) {
            Szturchnij();
            continue;
        }

        Odpowiedz(guess);
        next:;
    }

    return 0;
}
