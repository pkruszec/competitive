#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

void print_pow2(int x)
{
    if (x < 0) {
        cout << "0\n";
        return;
    }

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

vector<string> expand(string &s, unordered_map<char, int> &len)
{
    vector<string> n;
    for (auto c: s) {
        int count = len[c];
        string cstr(1, c);

        if (c == '0' || c == '1') {
            n.push_back(cstr);
        } else {
            for (int i = 1; i <= count; ++i)
                n.push_back(cstr + to_string(i));
        }
    }
    return n;
}

vector<vector<string>> get_components(unordered_map<string, vector<string>> &graph)
{
    unordered_set<string> visited;
    vector<vector<string>> components;

    for (auto &[v, n]: graph) {
        if (visited.find(v) != visited.end()) continue;
        vector<string> component;

        queue<string> q;
        q.push(v);
        visited.insert(v);
        component.push_back(v);

        while (!q.empty()) {
            string w = q.front();
            q.pop();

            for (auto u: graph[w]) {
                if (visited.find(u) != visited.end()) continue;
                visited.insert(u);
                q.push(u);
                component.push_back(u);
            }
        }

        components.push_back(component);
    }

    return components;
}

int count_bits(string &r, string &l, unordered_map<char, int> &len)
{
    vector<string> lhs = expand(l, len);
    vector<string> rhs = expand(r, len);
    if (lhs.size() != rhs.size()) return -1;
    int count = lhs.size();

    unordered_map<string, vector<string>> graph;

    for (int i = 0; i < count; ++i) {
        string left = lhs[i];
        string right = rhs[i];

        graph[left].push_back(right);
        graph[right].push_back(left);
    }

    vector<vector<string>> components = get_components(graph);

    // for (auto &s: lhs) {
    //     cout << s << " ";
    // } cout << "\n";
    // for (auto &s: rhs) {
    //     cout << s << " ";
    // } cout << "\n";

    // for (auto &[k, v]: graph) {
    //     cout << k << ": ";
    //     for (auto &s: v) {
    //         cout << s << " ";
    //     }
    //     cout << "\n";
    // }

    // for (auto &c: components) {
    //     cout << "-- ";
    //     for (auto x: c) cout << x << " ";
    //     cout << "\n";
    // }

    int result = 0;
    for (auto &c: components) {
        bool has_0 = (find(c.begin(), c.end(), "0") != c.end());
        bool has_1 = (find(c.begin(), c.end(), "1") != c.end());
        if (has_0 && has_1) return -1;
        if (has_0 || has_1) continue;
        result++;
    }

    return result;
}

int main(void)
{
    int n;
    cin >> n;

    while (n--) {
        int k;
        cin >> k;

        unordered_map<char, int> len;
        len['0'] = 1;
        len['1'] = 1;

        for (int i = 0; i < k; ++i) {
            cin >> len[i + 'a'];
        }

        int ll, rl;
        string l, r;
        cin >> ll >> l;
        cin >> rl >> r;

        print_pow2(count_bits(l, r, len));
    }

    return 0;
}
