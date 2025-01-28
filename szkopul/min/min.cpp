#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>

using namespace std;

void print_plus(int c)
{
    if (c < 1) return;

    cout << "(";
    print_plus(c-1);
    cout << "-)";
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n;
    cin >> n;

    vector<bool> plus(n-1, false);
    for (int i = 0; i < n-1; ++i) {
        string s;
        cin >> s;
        if (s == "+") {
            plus[i] = true;
        }
    }

    for (int i = 0; i < n-1; ++i) {
        if (!plus[i]) {
            cout << "-";
        } else {
            int cnt = 0;
            for (int j = i; j < n-1; ++j) {
                if (!plus[j]) break;
                cnt++;
            }
            
            print_plus(cnt);

            i += cnt-1;
        }
    }
    cout << "\n";

    return 0;
}

/*
-
-
+
+
-
+

a - b - c + d + e - f + g
a-b-((c-d)-e)-(f-g)
--((-)-)-(-)
--((-)-)-(-)

-+
a-b+c
a-(b-c)
-(-)

a-b-c
--

*/
