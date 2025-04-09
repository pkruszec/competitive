#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, vector<int>> graph;
vector<bool> visited;
vector<int> matching;

bool dfs(int v)
{
    if (visited[v]) return false;
    visited[v] = true;
    for (auto w: graph[v]) {
        if (matching[w] == -1 || dfs(matching[w])) {
            matching[w] = v;
            matching[v] = w;
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
        //edges.push_back({i, index});
        graph[i].push_back(index);
        graph[index].push_back(i);
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

    int m = strings.size();
    visited.resize(m, false);
    matching.resize(m, -1);

    bool any = false;
    do {
        any = false;
        for (int i = 0; i < m; ++i) {
            if (matching[i] == -1)
                any |= dfs(i);
        }
        for (int i = 0; i < m; ++i) visited[i] = false; 
    } while (!any);

    for (int i = 0; i < n; ++i) {
        out << strings[matching[i]] << "\n";
    }

    return 0;
}
