//
// Bezpieczeństwo minimalistyczne (bez)
// https://szkopul.edu.pl/problemset/problem/aSbIC_LB4H-CGMYPEVue5jFw/site/
//
// not solved
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <stdint.h>
#include <limits.h>
#include <string.h>

struct Edge {
    int u, v, b;
};

typedef int (*Fire)(int &pc, int &pn, int b);

int dfs(int *p, std::vector<bool> &vis, std::vector<Edge> &e, Fire fire, int v)
{
    vis[v] = true;

    int s = 0; 
    // std::cout << v+1 << ": p=" << p[v] << "\n";

    for (auto &edge: e) {

        int n = 0;
        if (edge.u == v) {
            n = edge.v;
        } else if (edge.v == v) {
            n = edge.u;
        } else {
            continue;
        }

        if (vis[n]) {
            continue;
        }

        // std::cout << "   " << n+1 << ": p=" << p[n] << " b=" << edge.b << "\n";

        s += fire(p[v], p[n], edge.b);
        s += dfs(p, vis, e, fire, n);
    }

    return s;
}

int main(void)
{
    int n, m;
    std::cin >> n >> m;

    int64_t sum_p = 0;
    int64_t sum_b = 0;

    std::vector<bool> vis (n, false);
    int *p = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
        sum_p += p[i];
    }

    std::vector<Edge> e;

    for (int i = 0; i < m; ++i) {
        int u, v, b;
        std::cin >> u >> v >> b;
        e.push_back(Edge{u - 1, v - 1, b});
        sum_b += b;
    }

    auto fire_min = [](int &pc, int &pn, int b) -> int {
        int limit = pc + pn - b;
        int fired = limit;
        int k = 0;

        if (pc > pn) {
            k = std::min(pc, limit);
            pc -= k;
            limit -= k;

            k = std::min(pn, limit);
            pn -= k;
            limit -= k;
        } else {
            k = std::min(pn, limit);
            pn -= k;
            limit -= k;

            k = std::min(pc, limit);
            pc -= k;
            limit -= k;
        }
        return fired;
    };

    auto fire_max = [](int &pc, int &pn, int b) -> int {
        int limit = pc + pn - b;
        int fired = limit;
        int k = 0;

        if (pc < pn) {
            k = std::min(pc, limit);
            pc -= k;
            limit -= k;

            k = std::min(pn, limit);
            pn -= k;
            limit -= k;
        } else {
            k = std::min(pn, limit);
            pn -= k;
            limit -= k;

            k = std::min(pc, limit);
            pc -= k;
            limit -= k;
        }
        return fired;
    };

    int *pt = new int[n];
    int min = INT_MAX;
    int max = INT_MAX;

    /*
    std::vector<int> nbors (n, 0);
    for (auto &edge: e) {
        nbors[edge.u]++;
        nbors[edge.v]++;
    }

    std::vector<std::pair<int, int>> valid;
    for (int i = 0; i < n; ++i) {
        if (nbors[i] <= 0) continue;

        valid.push_back(std::pair<int, int>(i, nbors[i]));
    }

    std::sort(valid.begin(), valid.end(), [](auto &p1, auto &p2) -> int { return p1.second < p2.second; });
*/
    /*
    for (auto &vv: valid) {
        std::cout << vv.first << ": " << vv.second << "   ";
    }
    std::cout << '\n';
*/

    for (int i = 0; i < n; ++i) {
        memcpy(pt, p, n*sizeof(int));

        int val = dfs(pt, vis, e, fire_min, i);
        if (val < min) min = val;
        std::fill(vis.begin(), vis.end(), false);
    }

    for (int i = 0; i < n; ++i) {
        memcpy(pt, p, n*sizeof(int));

        int val = dfs(pt, vis, e, fire_max, i);
        if (val < max) max = val;
        std::fill(vis.begin(), vis.end(), false);
    }
    /*
    for (int i = n-1; i >= 0; --i) {
        memcpy(pt, p, n*sizeof(int));

        int val = dfs(pt, vis, e, fire_min, i);
        if (val > max) max = val;
        std::fill(vis.begin(), vis.end(), false);
    }
    */

    // int min = dfs(p, vis, e, fire_min, 0);

    /*
    int diff = sum_p - sum_b;
    if (diff <= 0) {
        std::cout << "NIE\n";
        return 0;
    }
    */

    if (min == max) {
        std::cout << "NIE";
        return 0;
    }

    std::cout << min << " " << max << "\n";

    /*
    std::cout << sum_p << ", " << sum_b << "\n";

    for (auto &x: e) {
        std::cout << x.u << ", " << x.v << ", " << x.b << "\n";
    }
    */

    return 0;
}

