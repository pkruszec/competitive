//
// Bezpieczeństwo minimalistyczne (bez)
// https://szkopul.edu.pl/problemset/problem/aSbIC_LB4H-CGMYPEVue5jFw/site/
//
// not solved
//

#include <iostream>

int main(void)
{
    int n, m;
    std::cin >> n >> m;

    int *p = new int[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }
    
    int max_s = 0;
    int max_d = 0;
    for (int i = 0; i < m; ++i) {
        int u, v, b;
        std::cin >> u >> v >> b;
        u -= 1;
        v -= 1;

        int s = p[u] + p[v];
        int d = s - b;
        // std::cout << "sum: " << s << " diff: " << s - b << "\n";

        if (s > max_s) max_s = s;
        if (d > max_d) max_d = d;
    }

    std::cout << max_d << " " << max_s << '\n';
    return 0;
}

