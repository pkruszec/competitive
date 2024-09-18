//
// Anagramy
// https://szkopul.edu.pl/problemset/problem/Aq-3LEQBYOdbiqQXvn3TJ0Id/site/
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>
#include <unordered_map>

bool cmp(std::vector<std::string> *&a, std::vector<std::string> *&b)
{
    return ((*a)[0].compare((*b)[0])) < 0;
}

int main(void)
{
    int n;
    std::cin >> n;

    auto *s = new std::string[n];
    std::unordered_map<std::string, std::vector<std::string>> k;

    for (int i = 0; i < n; ++i) {
        std::cin >> s[i];

        std::string sx = s[i];
        std::sort(sx.begin(), sx.end());

        if (!k.count(sx)) {
            k[sx] = std::vector<std::string>{};
        }

        auto &vec = k.at(sx);
        bool con = false;
        for (auto &d: vec) {
            if (d == s[i]) {
                con = true;
                break;
            }
        }

        if (!con) vec.push_back(s[i]);
    }

    std::vector<std::vector<std::string> *> vs;

    for (auto &it: k) {
        std::sort(it.second.begin(), it.second.end());
        vs.push_back(&it.second);
    }

    std::sort(vs.begin(), vs.end(), cmp);

    for (auto &it: vs) {
        for (auto &e: *it) {
            std::cout << e << ' ';
        }
        std::cout << '\n';
    }

    return 0;
}
