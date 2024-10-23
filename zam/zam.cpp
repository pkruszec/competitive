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

    // TODO: cut left 9's and add c?

    int nine_count = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '9') nine_count++;
    }

    int last_non_zero = 0;
    tmp.clear();
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] == '9') break;
        int value = '0' + ('9' - s[i]);
        tmp.push_back(value);
        if (value != '0') last_non_zero = tmp.size() - 1;
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

    if (diff != 0 && diff <= s.size()) {
        c += diff;
        nine_count += last_non_zero+1;
        for (int i = 0; i < last_non_zero+1; ++i) {
            s[s.size() - 1 - i] = '9';
        }
    }

    // cout << diff << "\n";

    if (nine_count != s.size()) {
        int zero_count = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '0') {
                zero_count++;
                continue;
            }
            c += 9 - (s[i]-'0');
        }

        if (s[0] == '1' && zero_count == s.size() - 1) {
            if (zero_count > 0)
                cout << "1\n";
            else
                cout << "0\n";
            return 0;
        }

        /*
        if (s[s.size() - 1] != '0') {
            c += 9 - (s[s.size() - 1] - '0');
            s[s.size() - 1] = '9';
        }
        */

        // TODO: Draw it out for different cases
        //

        int idx = 0;
        bool had_non_9_before_last = false;
        bool had_9_before_last = false;
        bool sc = false;
        for (int i = s.size() - 1; i >= 0; --i) {
            // if (s[i] == '9' && pp) sc = false;
            // if (s[i] != '9') pp = true;

            if (i == s.size() - 1) continue;

            if ((s[i] == '9' && had_9_before_last)) sc = true;

            if (s[i] != '9') had_non_9_before_last = true;
            else had_9_before_last = true;

            if (sc && s[i] != '0') idx++;

            // if (s.size() < 100) cout << s[i];
        }
        // cout << " (" << idx << ") ";
        c += idx;

/*
        bool got_not_nine = false;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '0') continue;
            if (i == s.size() - 1) continue;
            if (s[i] == '9') {
                if (got_not_nine) break;
            } else {
                got_not_nine = true;
            }
            c++;
        }
*/

    }

    // cout << s << "\n";


#if 0
    int fst = 0;
    int nine_count = 0;
    for (int i = fst; i < s.size(); ++i) {
        if (s[i] == '9') nine_count++;
    }
    while (!got_it(s, fst)) {
        int digit_count = s.size() - fst;
        
        char last = s[s.size() - 1];
        int lx = last - '0';

        if (1) {
            if (lx == 9 && (nine_count == s.size() - fst)) {
                c += 2;
                break;
            }

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
#endif

    c += 2;
    cout << c << '\n';

    return 0;
}
