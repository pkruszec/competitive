#include "kaslib.h"

int main()
{
    long long n = DajN();

    while (true) {

        long long count = 0;
        long long guess = 0;
        for (long long i = n; i >= 1;) {
            // cout << DajX() << " -> " << i << "\n";

            if (count > 100000) {
                Szturchnij();
                goto next;
            }

            long long result = Pytaj(i);
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

        /*
        long long this_multiplier_count = 0;
        long long multiplier = 1;
        long long guess = -1;
        for (long long i = multiplier; i < n; i += multiplier) {
            this_multiplier_count++;
            int result = Pytaj(i);
            cout << DajX() << " -> " << i << " " << result << "\n";

            if (this_multiplier_count > n/1000) {
                this_multiplier_count = 0;
                Szturchnij();
                goto next;
            }

            if (result == i) {
                multiplier = i;
            } else if (result < i) {
                guess = i - multiplier;
            }
        }
        */

        Odpowiedz(guess);
        next:;
    }

    return 0;
}
