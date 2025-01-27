#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    int m, p, n;
    cin >> m >> p >> n;

    vector<vector<int>> b(m, vector<int>(m, -1));
    vector<vector<int>> gw(m, vector<int>(m, -1));
    queue<pair<int, int>> w;
    vector<int> colors;

    for (int i = 0; i < p; ++i) {
        int w, k, c;
        cin >> w >> k >> c;
        b[w-1][k-1] = c;
    }

    gw[0][0] = 0;
    w.push({0, 0});
    colors.push_back(0);
    int ip = 1;

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

                if (gw[w][k] == -1) {
                    cout << "-1\n";
                } else {
                    int r = gw[w][k];
                    int v = ip - r - 1;
                    cout << colors[colors.size() - 1 - v] << "\n";

                    // int which = ip - gw[w][k];
                    // cout << colors[(int)colors.size() - 1 - which] << "\n";
                    // cout << colors[colors.size() - 1 - (ip - gw[w][k])] << "\n";
                }
                continue;
            } break;
            default: break;
        }

        // cout<<"-- ";for (auto color: colors) {cout << color << " ";}cout << "\n";

        auto head = w.back();
        head.first += dy;
        head.second += dx;
        w.push(head);
        int &p = b[head.first][head.second];
        if (p != -1) {
            colors.push_back(p);
            p = -1;
        } else {
            auto tail = w.front();
            w.pop();
            gw[tail.first][tail.second] = -1;
        }
        gw[head.first][head.second] = ip++;


        // cout << "========================================\n";
        // for (int i = 0; i < m; ++i) {
        //     for (int j = 0; j < m; ++j) {
        //         int r = gw[i][j];
        //         int v = ip - r - 1;

        //         cout << setw(4);

        //         if (r < 0) {
        //             cout << ".";
        //         } else {
        //             cout << colors[colors.size() - 1 - v];
        //         }
        //     }   
        //     cout << "\n";
        // }
    }

    return 0;
}
