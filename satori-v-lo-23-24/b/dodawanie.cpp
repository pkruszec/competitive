//
// = Dodawanie
// https://satori.tcs.uj.edu.pl/contest/8652756/problems/8763675
//
#include <iostream>
#include <string>

static void add_digit(std::string &s, std::string &b)
{
    int carry = 0;
    int mx = std::max(s.size(), b.size());
    for (int i = 0; i < mx; ++i) {
        int sidx = s.size() - i - 1;
        int k = (sidx >= 0 && sidx < s.size()) ? (s[sidx] - '0') : 0;

        int bidx = b.size() - i - 1;
        int l = (bidx >= 0 && bidx < b.size()) ? (b[bidx] - '0') : 0;

        int r = k+l+carry;
        carry = r / 10;
        char v = '0' + r % 10;
        if (sidx < 0) {
            s.insert(0, 1, v);
        } else {
            s[sidx] = v;
        }
    }

    if (carry != 0) s.insert(0, 1, '0' + carry);
}

int main(void)
{
    std::string a, b;
    std::cin >> a >> b;

    add_digit(a, b);

    // int p = b.size() - 1;
    // int k = 1;
    // for (int i = p; i >= 0; --i) {
    //     int x = b[i] - '0';
    //     // add_digit(a, x*k);
    //     k *= 10;
    // }

    std::cout << a << '\n';

    return 0;
}
