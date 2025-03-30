#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define rep(n, i) for (auto i = 0; i < n; ++i)

typedef vector<pair<int, int>> Cards;

bool check(Cards &cards)
{
    int prev = min(cards[0].first, cards[0].second);
    for (int i = 1; i < cards.size(); ++i) {
        int best = min(cards[i].first, cards[i].second);
        int worst = max(cards[i].first, cards[i].second);
        if (prev <= best) {
            prev = best;
        } else if (prev <= worst) {
            prev = worst;
        } else {
            return false;
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    Cards cards(n);
    rep(n, i) {
        cin >> cards[i].first >> cards[i].second;
    }

    int m;
    cin >> m;
    rep(m, i) {
        int a, b;
        cin >> a >> b;
        a--;
        b--;

        {
            auto t = cards[a];
            cards[a] = cards[b];
            cards[b] = t;
        }

        bool yes = check(cards);
        cout << (yes ? "TAK" : "NIE") << "\n";

        // {
        //     auto t = cards[a];
        //     cards[a] = cards[b];
        //     cards[b] = t;
        // }
    }

    return 0;
}
