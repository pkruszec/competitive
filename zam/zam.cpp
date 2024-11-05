//
// Zamek cykliczny (zam)
// Paweł Kruszec
// not solved (35 pts)
//

#include <iostream>
#include <string>
#include <limits.h>
#include <stdint.h>

using namespace std;

int MAX = 1000000;

bool got_it(string &s, int fst)
{
    return (s.size() - fst) == 1 && s[fst] == '1';
}

bool inc(string &s, string &tmp, int &c, int &nine_count)
{
    //
    // Try to find how much we have to increment the last non-nine digits to all nines.
    // e.g.
    // 999980 -> 19
    // 999999 -> 0
    // 992222 -> 7777
    //
    // The result will be stored in tmp[0..last_non_zero+1],
    // starting from the least significant digit (backwards).
    //
    // If the last digit is 9, the result will be empty, which is equivalent in value to 0.
    //
    int brk_index = s.size()-1;
    int last_non_zero = 0;
    tmp.clear();
    for (int i = s.size() - 1; i >= 0; --i) {
        if (s[i] == '9') {
            brk_index = i;
            break;
        }
        int value = '0' + ('9' - s[i]);
        tmp.push_back(value);
        if (value != '0') last_non_zero = tmp.size() - 1;
    }

    int min_flip = 0;
    for (int i = brk_index; i >= 0; --i) {
        if (s[i] != '9') {
            min_flip = i;
            break;
        }
    }

    //
    // Try to parse the result as an integer.
    // If the result is too big to be represented, we set it to INT_MAX.
    // This is because if it's that big, it is definitely not beneficial to increment.
    //
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

    int compared = diff + min_flip;

    //
    // If it's beneficial to increment the number to ...999,  do it.
    // Just set the appropriate characters to nines and add diff to c.
    //
    if (diff != 0 && compared <= s.size()) {
        c += diff;
        nine_count += last_non_zero+1;
        for (int i = 0; i < last_non_zero+1; ++i) {
            s[s.size() - 1 - i] = '9';
        }
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

    //
    // Count all the nines.
    // This will be used later as a cache,
    // so that we don't have to check all the digits to see if we are done.
    //
    int nine_count = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '9') nine_count++;
    }

    inc(s, tmp, c, nine_count);

    //
    // If the increments were sufficient to cover the entire number, skip this step.
    // Otherwise, we have to do a little bit more calculation.
    //
    if (nine_count != s.size()) {

        //
        // The first step here is to check if the number is 100000... (one and zeroes)
        // If it is, we don't have to do anything else.
        // TODO: It would be best to arrange the algorithm in such a way
        //       that this step is not needed.
        //       Maybe it doesn't matter though.
        //

        int zero_count = 0;
        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '0') {
                zero_count++;
                continue;
            }
        }

        if (s[0] == '1' && zero_count == s.size() - 1) {
            if (zero_count > 0)
                cout << "1\n";
            else
                cout << "0\n";
            return 0;
        }

        //
        // This is the part that we haven't figured out yet.
        // We need to count:
        // - how many increments we have to do
        // - how many shifts we have to do
        // Maybe it is not a bad idea to simulate this step.
        // On this step, we are sure:
        // - the number is not 999999999...
        // - the number is not 1
        // - the number is not 100000...
        // because if it was, main() already returned.
        // We don't know anything else about the number.
        //

        int fst = 0;
        while (!got_it(s, fst)) {
            char last = s[s.size() - 1];
            int lx = last - '0';
            if (lx == 0 || lx == 9) {
                if (nine_count == s.size() - fst) {
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
    }

    c += 2;
    cout << c << '\n';

    return 0;
}
