#include <iostream>

int main(void) {
    int z;
    std::cin >> z;
    for (int zi = 0; zi < z; ++zi) {
        int n, m;
        std::cin >> n >> m;
        int *k = new int[n];
        for (int j = 0; j < n; ++j) std::cin >> k[j];

        auto *c = new std::pair<int, int>[m];
        for (int j = 0; j < m; ++j) {
            int a, b;
            std::cin >> a >> b;
            c[j].first = a;
            c[j].second = b;
        }
    }
    return 0;
}
