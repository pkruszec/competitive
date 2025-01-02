#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <stdint.h>

using namespace std;

bool is_variable(char c)
{
    return c >= 'a' && c <= 'z';
}

char var(char c)
{
    if (c == 0) return '0';
    if (c == 1) return '1';
    return c;
}

int count(vector<pair<char, int>> &V, vector<pair<int, int>> &E, vector<int> &visited, int start_v, int &ci)
{
    if (visited[start_v]) return 0;

    queue<int> Q;
    Q.push(start_v);
    visited[start_v] = ci;

    bool flag = false;

    bool has_0 = false;
    bool has_1 = false;

    while (!Q.empty()) {
        int v = Q.front();
        Q.pop();

        if (V[v].first == '0') {
            flag = true;
            has_0 = true;
        } else if (V[v].first == '1') {
            flag = true;
            has_1 = true;
        }

        if (has_0 && has_1) {
            return -1;
        }

        for (auto &[a, b]: E) {
            int w;
            if (a == v) {
                w = b;
            } else if (b == v) {
                w = a;
            } else continue;
            if (visited[w]) continue;
            visited[w] = ci;

            Q.push(w);
        }
    }

    ci += 1;

    if (has_0 && has_1) {
        return -1;
    }

    return flag ? 0 : 1;
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

void print_dot_graph(vector<pair<char, int>> &V, vector<pair<int, int>> &E)
{
    cout << "graph {\n";
    for (auto &[a, b]: E) {
        cout << "\"" << V[a].first;
        if (V[a].second) cout << V[a].second;
        cout << "\"";

        cout << " -- ";

        cout << "\"" << V[b].first;
        if (V[b].second) cout << V[b].second;
        cout << "\"";

        cout << "\n";
    }
    cout << "}\n";
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int x;
    cin >> x;

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
                continue;
            } else {
                cout << "1\n";
                continue;
            }
        }

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

        unordered_map<char, int> Or;
        unordered_map<char, int> Ol;
        vector<pair<char, int>> V;
        vector<pair<int, int>> E;

        auto push_vertex = [&](unordered_map<char, int> &O, char c) -> int {
            if (c == '0' || c == '1') {
                for (int i = 0; i < V.size(); ++i) {
                    if (V[i].first == c) return i;
                }
                V.push_back(pair<int, int>(c, 0));
            } else {

                // O[c] += 1;
                // int o = O[c];

                int l = lengths[c - 'a'];
                int o = (O[c] % l) + 1;
                O[c] += 1;

                for (int i = 0; i < V.size(); ++i) {
                    if (V[i].first == c && V[i].second == o) return i;
                }
                V.push_back(pair<int, int>(c, o));
            }
            return V.size() - 1;
        };

        for (int i = 0; i < len; ++i) {
            int v = push_vertex(Or, rhs_exp[i]);
            int w = push_vertex(Ol, lhs_exp[i]);
            E.push_back(pair<int, int>(v, w));
        }

        // print_dot_graph(V, E);

        vector<int> visited(V.size(), 0);
        int cc = 0;
        int ci = 1;
        for (int i = 0; i < V.size(); ++i) {
            int r = count(V, E, visited, i, ci);
            if (r < 0) {
                cout << "0\n";
                goto next_eq;
            }
            cc += r;
        }

        print_pow2(cc);

        next_eq:;
    }

    return 0;
}
