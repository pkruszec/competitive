#include <stdlib.h>
#include <time.h>

#include "porlib.h"

// Inwersja -- ile elementów po tym elemencie jest mniejszych?
// Jeżeli po zamianie i, j liczba inwersji zwiększyła się, p[i] był mniejszy od p[j].

int main()
{
    srand(time(0));

    int n = DajN();

    for(int i = 1; i <= n; ++i)
    {
        int z = Zamiana(1, i);
        Zamiana(1, i);
    }

    return 0;
}
