#include <iostream>
#include <random>
#include <string>
#include <assert.h>
#include <numeric>

using namespace std;

namespace {
// Można zmienić te wartości.
long long N = 1'000'000'000'000'000'000ll;
int bajtalary = 10'000'000;

// Aby zmienić losowość należy zamienić 1 na dowolną inną liczbę typu int.
mt19937_64 rng(1);

long long X;
bool czy_zainicjalizowany = false;
int wygrane = 0;

long long miss_count = 0;
long long hit_count = 0;
long long ask_count = 0;

long long wylosuj_liczbe() {
    return uniform_int_distribution<long long>(1, N)(rng);
}

void inicjalizuj_gre() {
    X = wylosuj_liczbe();
}

void inicjalizuj_interakcje() {
    if (czy_zainicjalizowany) return;
    inicjalizuj_gre();
    czy_zainicjalizowany = true;
}

void proba_zakonczenia() {
    if (!bajtalary) {
        cout << "hit: " << hit_count
             << " miss: " << miss_count
             << " ask: " << ask_count
             << " avg " << ((ask_count)/(hit_count+miss_count)) << "/b"
             << " per " << ((ask_count+miss_count)/hit_count) << "/b ";
    	cout << "Liczba wygranych: " << to_string(wygrane) << endl;
    	exit(0);
    }
}

void zjedz_bajtalara() {
    proba_zakonczenia();
    --bajtalary;
}
}

long long DajN() {
    inicjalizuj_interakcje();
    return N;
}

long long DajX() {
    inicjalizuj_interakcje();
    return X;
}

long long Pytaj(long long y) {
    ask_count++;
    inicjalizuj_interakcje();
    assert(1 <= y && y <= N);
    zjedz_bajtalara();
    proba_zakonczenia();
    return gcd(X, y);
}

void Szturchnij() {
    miss_count++;
    inicjalizuj_interakcje();
    zjedz_bajtalara();
    X = wylosuj_liczbe();
    proba_zakonczenia();
}

void Odpowiedz(long long y) {
    hit_count++;    
    inicjalizuj_interakcje();
    assert(1 <= y && y <= N);
    zjedz_bajtalara();
    assert(X == y);
    ++wygrane;
    proba_zakonczenia();
    inicjalizuj_gre();
}
