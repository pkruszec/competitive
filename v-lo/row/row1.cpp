#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <stdint.h>

using namespace std;

#if MEASURE
uint64_t Counter;

#define Measure(s) \
    do { \
        if (Counter == 0) { \
            Counter = __rdtsc(); \
        } else { \
            uint64_t old = Counter; \
            Counter = __rdtsc(); \
            cout << s << ": "<< ((float)(Counter-old) / 100000.f) << "\n"; \
        } \
    } while (0);
#else
#define Measure(s)
#endif

bool is_variable(char c)
{
    return c >= 'a' && c <= 'z';
}

int count(vector<pair<int, int>> &E, unordered_map<int, bool> &visited, int start_v)
{
    if (visited[start_v]) return 0;

    queue<int> Q;
    Q.push(start_v);
    visited[start_v] = true;

    bool has_0 = false;
    bool has_1 = false;

    while (!Q.empty()) {
        auto v = Q.front();
        Q.pop();

        if (v == 0) {
            has_0 = true;
        } else if (v == 1) {
            has_1 = true;
        }

        for (auto &[a, b]: E) {
            int w;
            if (a == v) {
                w = b;
            } else if (b == v) {
                w = a;
            } else continue;
            if (visited[w]) continue;
            visited[w] = true;

            Q.push(w);
        }
    }

    if (has_0 && has_1) {
        return -1;
    }

    return (has_0||has_1) ? 0 : 1;
}

void print_pow2(int x)
{
    if (x == 0) {
        cout << "1\n";
        return;
    }

    if (x < 64) {
        uint64_t y = (uint64_t)0xFFFFFFFFFFFFFFFF;
        y = (y >> (64-x)) + 1;
        cout << y << "\n";
        return;
    }

    string D(3020, 0);
    D[D.size() - 1] = 1;

    int min_i = 0;
    while (x--) {
        int carry = 0;
        for (int i = D.size() - 1; i >= 0; --i) {
            D[i] *= 2;
            D[i] += carry;
            carry = D[i]/10;
            D[i] %= 10;

            if (i < min_i) {
                min_i = i;
                break;
            }
        }
    }

    int idx = 0;
    for (int i = 0; i < D.size(); ++i) {
        if (D[i] != 0) break;
        idx++;
    }

    for (int i = idx; i < D.size(); ++i) {
        cout << (int)D[i];
    }
    cout << "\n";
}

void print_dot_graph(vector<pair<int, int>> &E)
{
    auto f = [](int x) -> char {
        if (x == 0) return '0';
        if (x == 1) return '1';

        return x - 2 + 'a';
    };

    unordered_map<int, int> Ol;
    unordered_map<int, int> Or;

    auto o = [&](int x, bool r) {
        if (x == 0 || x == 1) return;

        if (r) cout << ++Or[x];
        else   cout << ++Ol[x];
    };

    cout << "graph {\n";
    for (auto &[a, b]: E) {
        cout << "\"" << f(a);
        o(a, false);
        cout << "\"";

        cout << " -- ";

        cout << "\"" << f(b);
        o(b, true);
        cout << "\"";

        cout << "\n";
    }
    cout << "}\n";
}

int main(void)
{
    Measure("");

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int x;
    cin >> x;

    vector<pair<int, int>> E;

    while (x--) {

        int k;
        cin >> k;

        int lengths[26] = {};
        for (int i = 0; i < k; ++i) {
            cin >> lengths[i];
        }

        int lhs_len = 0;
        string lhs;
        cin >> lhs_len >> lhs;

        int rhs_len = 0;
        string rhs;
        cin >> rhs_len >> rhs;

        if (k == 0) {
            if (lhs_len != rhs_len || lhs != rhs) {
                cout << "0\n";
            } else {
                cout << "1\n";
            }
            continue;
        }

        Measure("gather");

        lhs_len = 0;
        for (auto c: lhs) {
            if (is_variable(c)) {
                lhs_len += lengths[c - 'a'];
            } else {
                lhs_len++;
            }
        }

        rhs_len = 0;
        for (auto c: rhs) {
            if (is_variable(c)) {
                rhs_len += lengths[c - 'a'];
            } else {
                rhs_len++;
            }
        }

        Measure("length");

        if (lhs_len != rhs_len) {
            cout << "0\n";
            continue;
        }

        int len = lhs_len = rhs_len;

        string lhs_exp(len, 0);
        string rhs_exp(len, 0);
        int pos;

        pos = 0;
        for (auto c: lhs) {
            if (is_variable(c)) {
                for (int i = 0; i < lengths[c - 'a']; ++i) {
                    lhs_exp[pos++] = c;
                }
            } else {
                lhs_exp[pos++] = c;
            }
        }

        pos = 0;
        for (auto c: rhs) {
            if (is_variable(c)) {
                for (int i = 0; i < lengths[c - 'a']; ++i) {
                    rhs_exp[pos++] = c;
                }
            } else {
                rhs_exp[pos++] = c;
            }
        }

        Measure("expand");

        unordered_set<int> V;
        unordered_map<char, int> Or;
        unordered_map<char, int> Ol;

        E.clear();
        V.insert(0);
        V.insert(1);

        // int xx = 2;
        // int lp = 0;
        // int rp = 0;
        // int li = 0;
        // int ri = 0;
        for (int i = 0; i < len; ++i) {
            char lc = lhs_exp[i];
            char rc = rhs_exp[i];

            // li++;
            // ri++;
            // if (lc == '0' || lc == '1' || li >= lengths[lc - 'a']) {
            //     lp++;
            //     li = 0;
            // }
            // if (rc == '0' || rc == '1' || ri >= lengths[rc - 'a']) {
            //     rp++;
            //     ri = 0;
            // }

            int l, r;
            
            if (lc == '0') {
                l = 0;
            } else if (lc == '1') {
                l = 1;
            } else {
                l = 2 + (++Ol[lc])*k + (lc - 'a');
            }

            if (rc == '0') {
                r = 0;
            } else if (rc == '1') {
                r = 1;
            } else {
                r = 2 + (++Or[rc])*k + (rc - 'a');
            }

            if (l >= 2) V.insert(l);
            if (r >= 2) V.insert(r);
            if (1|| l != r) E.push_back(pair<int, int>(l, r));

            // int lo = 0;
            // int ro = 0;

            // if (lc != '0' && lc != '1') {
            //     int l = lengths[lc - 'a'];
            //     lo = (Ol[lc] % l) + 1;
            //     Ol[lc] += 1;
            // }

            // if (rc != '0' && rc != '1') {
            //     int l = lengths[rc - 'a'];
            //     ro = (Or[rc] % l) + 1;
            //     Or[rc] += 1;
            // }

            // auto l = Vertex{lc, lo};
            // auto r = Vertex{rc, ro};

            // if (l != r) {
            //     V.insert(r);
            //     E.push_back(pair<Vertex, Vertex>(l, r));
            // }
        }

        Measure("graph");

        // print_dot_graph(E);

        unordered_map<int, bool> visited;
        // vector<bool> visited(256, false);
        int cc = 0;

        for (auto v: V) {
            int r = count(E, visited, v);
            if (r < 0) {
                cout << "0\n";
                goto next_eq;
            }
            cc += r;
        }

        Measure("traverse");

        print_pow2(cc);

        Measure("print");

        next_eq:;
    }

    return 0;
}
