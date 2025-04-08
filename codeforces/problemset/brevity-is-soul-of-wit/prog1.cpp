#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct Edge {
    int v;
    int w;
};

vector<int> mt;
vector<bool> used;

bool kuhn(int v, vector<Edge> &edges)
{
    if (used[v]) return false;
    used[v] = true;
    for (auto &e: edges) {
        int to;
        if (e.v == v) {
            to = e.w;
        } else if (e.w == v) {
            to = e.v;
        } else continue;

        if (mt[to] == -1 || kuhn(mt[to], edges)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;
    vector<string> strings(n);
    vector<Edge> edges;

    auto add = [&](string s, int i) {
        //out << s << "\n";
        int index = -1;
        for (int j = n; j < strings.size(); ++j) {
            if (strings[j] == s) {
                index = j;
                break;
            }
        }
        if (index < 0) {
            strings.push_back(s);
            index = strings.size() - 1;
        }
        edges.push_back({i, index});
    };

    auto add_i = [&](int i) {
        for (int j = 0; j < strings[i].size(); ++j) {
            char a = strings[i][j];
            add({a}, i);
            for (int k = j+1; k < strings[i].size(); ++k) {
                char b = strings[i][k];
                add({a, b}, i);
                for (int l = k+1; l < strings[i].size(); ++l) {
                    char c = strings[i][l];
                    add({a, b, c}, i);
                    for (int m = l+1; m < strings[i].size(); ++m) {
                        char d = strings[i][m];
                        add({a, b, c, d}, i);
                    }
                }
            }
        }
    };

    for (int i = 0; i < n; ++i) {
        in >> strings[i];
    }
    
    for (int i = 0; i < n; ++i) {
        add_i(i);
    }

    mt.resize(strings.size(), -1);
    used.resize(strings.size(), false);
    for (int i = 0; i < n; ++i) {
        cout << kuhn(i, edges) << "\n";
    }

    vector<int> sol(n, -1);
    for (int i = 0; i < strings.size(); ++i) {
        if (mt[i] >= 0 && mt[i] < n && sol[mt[i]] == -1) {
            sol[mt[i]] = i;
        }
    }
    for (auto x: sol) {
        if (x==-1) {
            out << "-1\n";
            return 0;
        }
    }

    for (auto x: sol) {
        out << strings[x] << "\n";
    }

    // for (auto &s: strings) {
    //     cout << s << "\n";
    // }
    // cout << strings.size() << "\n";
    // cout << edges.size() << "\n";

    // cout << "graph {\n";
    // for (auto &e: edges) {
    //     cout << "  " << strings[e.v] << " -> " << strings[e.w] << "\n";
    // }
    // cout << "}\n";

    /*
    vector<int> xx(n);
    for (int i = 0; i < n; ++i) {
        xx[i] = i;
    }
    sort(xx.begin(), xx.end(), [&](int x, int y) {
        return strings[x].size() < strings[y].size();
    });

    for (int j = 0; j < n; ++j) {
        int i = xx[j];
        bool found = false;
        for (auto &e: edges) {
            int w;
            if (e.v == i) {
                w = e.w;
            } else if (e.w == i) {
                w = e.v;
            } else continue;
            if (e.visited) continue;

            bool ok = true;
            for (auto &f: edges) {
                if (f.w != w && f.v != w) continue;
                if (f.visited) {
                    ok = false;
                    break;
                }
            }
            if (!ok) continue;

            e.visited = true;
            solutions[i] = strings[w];
            found = true;

            cout << strings[i] << ": " << solutions[i] << "\n";
            break;
        }

        if (!found) {
            cout << "not found for " << strings[i] << "\n";
            out << "-1\n";
            return 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        out << solutions[i] << "\n";
    }
    */

    return 0;
}
