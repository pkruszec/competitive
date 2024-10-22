#include <iostream>
#include <string>
#include <limits.h>
#include <stdint.h>
//#include <string_view>

using namespace std;

int MAX = 1000000;

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

    string tmp;
    tmp.reserve(1024);

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
        // cout << c << ": " << s.substr(fst) << "\n";

        int digit_count = s.size() - fst;
        
        char last = s[s.size() - 1];
        int lx = last - '0';
        // if (lx == 0 || lx == 9) {
        if (1) {
            if (lx == 9 && (nine_count == s.size() - fst)) {
                c += 2;
                break;
            }

            // TODO: get last part without 9
            // for example
            // 999980
            //     ^^
            // and add to 99
            //

            int last_non_zero = 0;
            tmp.clear();
            for (int i = s.size() - 1; i >= fst; --i) {
                if (s[i] == '9') break;
                int value = '0' + ('9' - s[i]);
                tmp.push_back(value);
                if (value != '0') last_non_zero = tmp.size() - 1;
                // TODO? probably not needed
                // if (tmp.size() > digit_count) break;
            }

            // cout << tmp.substr(0, last_non_zero+1) << "\n";

            int diff = 0;
            int r = 1;
            for (int i = 0; i <= last_non_zero; ++i) {
                if (tmp[i] == '0')
                    diff *= 10;
                else
                    diff += r * (tmp[i] - '0');
                
                if (diff > MAX || diff < 0) {
                    diff = INT_MAX;
                    break;
                }
                r *= 10;
            }

            // cout << diff << "\n";
            if (diff != 0 && diff <= digit_count) {
                c += diff;
                nine_count += last_non_zero+1;
                for (int i = 0; i < last_non_zero+1; ++i) {
                    s[s.size() - 1 - i] = '9';
                }
                continue;
            }

            if (s[s.size() - 1] != '0' && s[s.size() - 1] != '9'/* && s[fst] >= s[s.size() - 1]*/) {
                c += 9-lx;
                s[s.size() - 1] = '9';
                nine_count++;
                continue;
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
