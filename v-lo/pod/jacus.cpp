#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

bool mozliwe(int *ciag, int len, int k, int limit) {
    int count = 1;
    int suma = 0;
    for (int i = 0; i < len; ++i) {
        int liczba = ciag[i];
        suma += liczba;
        if (suma > limit) {
            suma = liczba;
            count++;
        }
    }
    return count <= k;
}

int najmniejszaSuma(int *ciag, int count, int k, int max, int64_t sum) {
    // int dolna = *max_element(ciag.begin(), ciag.end());
    // int gorna = accumulate(ciag.begin(), ciag.end(), 0);

    int dolna = 0;
    int64_t gorna = 0;
    for (int i = 0; i < count; ++i) {
        if (ciag[i] > dolna) dolna = ciag[i];
    }
    for (int i = 0; i < count; ++i) {
        gorna += ciag[i];
    }

    // int dolna = max;
    // int gorna = sum;
    while (dolna < gorna) {
        int srodek = dolna + (gorna - dolna) / 2;
        if (mozliwe(ciag, count, k, srodek)) {
            gorna = srodek;
        } else {
            dolna = srodek + 1;
        }
    }
    return dolna;
}

#ifndef UNIT_TESTING
int main() {
    int n;
    int k;
    int wynik;
    cin >> n >> k;
    vector<int> ciag(n);
    for (int i = 0; i < n; i++) {
        cin >> ciag[i];
    }
    wynik = najmniejszaSuma(ciag.data(), ciag.size(), k, 0, 0);
    cout << wynik << endl;
    return 0;
}
#endif // UNIT_TESTING