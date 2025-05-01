#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int v, w, c;
};

vector<Edge> E;

int main()
{
    int n, k;
    cin >> n >> k;
    E.resize(n - 1);

    for (int i = 0; i < n; ++i) {
        cin >> E[i].v >> E[i].w >> E[i].c;
    }

    return 0;
}
