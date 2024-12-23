#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m, p, n;
    cin >> m >> p >> n;

    vector<vector<int>> b(m, vector<int>(m, -1));
    
    vector<int> eaten;
    vector<pair<int, int>> pos;
    pair<int, int> head(0, 0);

    pos.push_back(head);
    eaten.push_back(0);

    for (int i = 0; i < p; ++i) {
        int w, k, c;
        cin >> w >> k >> c;
        b[w-1][k-1] = c;
    }

    for (int i = 0; i < n; ++i) {
        char op;
        cin >> op;

        int dx = 0;
        int dy = 0;

        switch (op) {
            case 'L': {
                dx = -1;
            } break;
            case 'P': {
                dx = 1;
            } break;
            case 'G': {
                dy = -1;
            } break;
            case 'D': {
                dy = 1;
            } break;
            case 'Z': {
                int w, k;
                cin >> w >> k;
                w--;
                k--;

                int c = eaten.size();
                for (int j = 0; j < c; ++j) {
                    int i = pos.size() - 1 - j;
                    int h = eaten.size() - 1 - j;

                    if (pos[i].first == k && pos[i].second == w) {
                        cout << eaten[h] << "\n";
                        goto cc;
                    }
                }

                cout << "-1\n";
                cc:
                continue;
            } break;
            default: break;
        }

        head.first += dx;
        head.second += dy;
        pos.push_back(head);

        if (b[head.second][head.first] >= 0) {
            eaten.push_back(b[head.second][head.first]);
            b[head.second][head.first] = -1;
        }

    }

    return 0;
}
