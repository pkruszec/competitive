#include <stdlib.h>
#include <time.h>

#include "porlib.h"

// Inwersja -- ile elementów po tym elemencie jest mniejszych?
// Jeżeli po zamianie i, j liczba inwersji zwiększyła się, p[i] był mniejszy od p[j].

int main()
{
    srand(time(0));

    int n = DajN();
    int p = Zamiana(1, 1);

    while(1)
    {
        int i = 1 + rand()%(n);
        int j = 1 + rand()%(n);

        int z = Zamiana(i, j);
        if(z == 0) break;
        if(z > p)
        {
            Zamiana(i, j);
        }
        else
        {
            p = z;
        }
    }

    return 0;
}
