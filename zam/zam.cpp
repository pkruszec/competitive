#include <iostream>
#include <string>
//#include <string_view>

using namespace std;

bool got_it(string &s, int fst)
{
    return (s.size() - fst) == 1 && s[fst] == '1';
}

bool only_nines(string &s, int fst)
{
    for (int i = fst; i < s.size(); ++i) {
        if (s[i] != '9') return false;
    }
    return true;
}

int main()
{ 
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string s;
    s.reserve(1024*1024*4);
    cin >> s;

    int c = 0;
    int fst = 0;

    // TODO: liczyć różnicę między 10^ilość cyfr n a n
    // jeśli jest większa niż 1000000 (max) to ustawić na INT_MAX
    // i porównać z liczbą cyfr
    // jeśli mniejsza to 1 przycisk razy różnica
    // jeśli większa to flip

    int nine_count = 0;
    for (int i = fst; i < s.size(); ++i) {
        if (s[i] == '9') nine_count++;
    }

    while (!got_it(s, fst)) {
        cout << s.substr(fst) << "\n";

        char last = s[s.size() - 1];
        int lx = last - '0';
        if (lx == 0 || lx == 9) {
            if (lx == 9 && (nine_count == s.size() - fst)) {
                c += 2;
                break;
            }

            s.push_back(s[fst]);
            c++;
            fst++;

            for (int i = fst; i < s.size(); ++i) {
                if (s[i] != '0') {
                    fst = i;
                    break;
                }
            }

        } else {
            c += 9-lx;
            s[s.size() - 1] = '9';

            nine_count++;
        }
    }

    // cerr << s.capacity() << '\n';
    cout << c << '\n';

    return 0;
}
