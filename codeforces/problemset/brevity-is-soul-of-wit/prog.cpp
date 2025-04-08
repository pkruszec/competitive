#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <set>

using namespace std;

using Set = vector<string>;

void gen(string &s, Set &v)
{
    unordered_set<string> tmp;
    for (int j = 0; j < s.size(); ++j) {
        char a = s[j];
        tmp.insert({a});
        for (int k = j+1; k < s.size(); ++k) {
            char b = s[k];
            tmp.insert({a, b});
            for (int l = k+1; l < s.size(); ++l) {
                char c = s[l];
                tmp.insert({a, b, c});
                for (int m = l+1; m < s.size(); ++m) {
                    char d = s[m];
                    tmp.insert({a, b, c, d});
                }
            }
        }
    }

    for (auto s: tmp) {
        v.push_back(s);
    }
}

int main()
{
    ifstream in("input.txt");
    ofstream out("output.txt");

    int n;
    in >> n;
    vector<string> str(n);
    vector<Set> G(n);
    for (int i = 0; i < n; ++i) {
        string s;
        in >> s;
        str[i] = s;
        gen(s, G[i]);

        // sort(G[i].begin(), G[i].end(), [](auto &a, auto &b){
        //     return a.size() > b.size();
        // });

        //G[i].erase(unique(G[i].begin(), G[i].end()), G[i].end());
    }

    vector<string> ans(n);
    for (int i = 0; i < n; ++i) {
        auto &g = G[i];
        bool ok = false;
        for (auto &s: g) {
            bool stop = false;
            for (int j = 0; j < i; ++j) {
                if (ans[j] == s) {
                    stop = true;
                    break;
                }
            }
            if (stop) continue;

            ans[i] = s;
            ok = true;
            break;
        }

        if (!ok) {
            out << "-1\n";
            return 0;
        }
    }

    for (int i = 0; i < n; ++i) {
        out << ans[i] << "\n";
    }

    // for (int i = 0; i < n; ++i) {
    //     auto &v = G[i];
    //     cout << str[i] << "\n";
    //     for (auto &s: v) {
    //         cout << "    " << s << "\n";
    //     }
    //     cout << "\n";
    // }

    return 0;
}