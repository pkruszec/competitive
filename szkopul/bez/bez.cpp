//
// Paweł Kruszec <pakruszec@gmail.com>
// Bezpieczeństwo minimalistyczne (bez)
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

#define NOT_POSSIBLE INT_MIN

struct Edge {
    int u, v, b;
};

typedef int (*Fire)(int&, int&, int, bool);

bool is_adj(std::vector<Edge> &e, std::vector<bool> &vis, int v)
{
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
            return true;
        }
    }
    return false;
}

bool is_correct(int *p, std::vector<Edge> &e)
{
    for (auto &edge: e) {
        int b = edge.b;
        int u = p[edge.u];
        int v = p[edge.v];
        
        // std::cerr << "" << edge.u+1 << " -> " << edge.v+1 << ": " << u << "+" << v << ", " << b << "\n";
        if (u + v != b) {
            // std::cerr << "INCORRECT(" << edge.u+1 << " -> " << edge.v+1 << "): " << u << "+" << v << " != " << b << "\n";
            return false;
        }
    }
    return true;
}

int dfs(int *p, std::vector<bool> &vis, std::vector<Edge> &e, Fire fire, int v)
{
    vis[v] = true;
    int s = 0; 
    
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
        
        int res = 0;
        bool adj = is_adj(e, vis, v);
        vis[n] = true;
        
        res = fire(p[v], p[n], edge.b, adj);
        if (res == NOT_POSSIBLE) {
            return NOT_POSSIBLE;
        }
        s += res;
        
        res = dfs(p, vis, e, fire, n);
        if (res == NOT_POSSIBLE) {
            return NOT_POSSIBLE;
        }
        s += res;
    }
    
    return s;
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);
    
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
    
    if (sum_p <= sum_b) {
        std::cout << "NIE\n";
        return 0;
    }
    
    auto fire = [](int &pc, int &pn, int b, bool adj) -> int {
        int limit = pc + pn - b;
        int fired = limit;
        int k = 0;
        
        if (limit < 0) return NOT_POSSIBLE;
        if (adj && pc > b) return NOT_POSSIBLE;
        
        k = std::min(pc, limit);
        pc -= k;
        limit -= k;
        
        k = std::min(pn, limit);
        pn -= k;
        limit -= k;
        
        return fired;
    };
    
    auto fire_max = [](int &pc, int &pn, int b, bool adj) -> int {
        // std::cout << "pc=" << pc << ",pn=" << pn << ",adj=" << adj << ",b=" << b << '\n';
        
        int limit = pc + pn - b;
        int fired = limit;
        int k = 0;
        
        if (adj && pc > b) return NOT_POSSIBLE;
        
        k = std::min(pc, limit);
        pc -= k;
        limit -= k;
        
        k = std::min(pn, limit);
        pn -= k;
        limit -= k;
        
        return fired;
    };
    
    int *pt = new int[n];
    int min = INT_MAX;
    int max = INT_MIN;
    
    for (int i = 0; i < n; ++i) {
        memcpy(pt, p, n*sizeof(int));
        int val = dfs(pt, vis, e, fire, i);
        if (val != NOT_POSSIBLE) {
            if (val < min) {
                min = val;
            }
            if (val > max) {
                max = val;
            }
        }
        std::fill(vis.begin(), vis.end(), false);
    }
    
    if (min == INT_MAX || max == INT_MIN) {
        std::cout << "NIE\n";
        return 0;
    }
    
    std::cout << min << " " << max << "\n";
    
    return 0;
}

