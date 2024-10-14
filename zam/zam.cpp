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

    while (!got_it(s, fst)) {
        // cout << s.substr(fst) << "\n";

        char last = s[s.size() - 1];
        int lx = last - '0';
        if (lx == 0 || lx == 9) {
            if (lx == 9 && only_nines(s, fst)) {
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
        }
    }

    // cerr << s.capacity() << '\n';
    cout << c << '\n';

    return 0;
}
