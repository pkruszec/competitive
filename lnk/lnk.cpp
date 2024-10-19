#include <iostream>
#include <vector>
#include <algorithm>
#include <limits.h>

using namespace std;

int main()
{
    int links = 0;
    int n1, n2;
    cin >> n1 >> n2;

    vector<int> v1(n1);
    vector<int> v2(n2);


    for (int i = 0; i < n1; ++i) {
        cin >> v1[i];
    }
    for (int i = 0; i < n2; ++i) {
        cin >> v2[i];
    }

    vector<pair<int, int>> conn {};
    for (int i = 0; i < n1; ++i) {
        for (int j = 0; j < n2; ++j) {
            if (v1[i] != v2[j]) continue;

            conn.push_back(pair<int, int>(i, j));
        }
    }

    vector<int> cross_counts(conn.size(), 0);
    vector<bool> visited(conn.size(), false);
    vector<bool> removed(conn.size(), false);

    vector<pair<int, int>> crosses {};

    for (int i = 0; i < conn.size(); ++i) {
        auto &p = conn[i];

        for (int j = 0; j < conn.size(); ++j) {
            if (i == j) continue;
            auto &r = conn[j];

            if (r.first >= p.first && r.second <= p.second) {
                cross_counts[i]++;
                cross_counts[j]++;

                crosses.push_back(pair<int, int>(i, j));
            }      
        }
    }

    // count all connections with 0 crosses
    for (int i = 0; i < cross_counts.size(); ++i) {
        if (cross_counts[i] == 0) {
            links++;
            visited[i] = true;
        }
    }

    for (auto &c: crosses) {
        int idx;
        int snd;
        if (removed[c.first] || removed[c.second]) {
            continue;
        }

        if (cross_counts[c.first] < cross_counts[c.second]) {
            idx = c.first;
            snd = c.second;
        } else {
            idx = c.second;
            snd = c.first;
        }

        if (!visited[idx]) {
            // cout << conn[idx].first << ";" << conn[idx].second << "(" << cross_counts[idx] << ")" << ">" << conn[snd].first << ";" << conn[snd].second << "(" << cross_counts[snd] << ")" << " ";
            links++;
        }

        cross_counts[idx]--;
        cross_counts[snd]--;
        visited[idx] = true;
        removed[snd] = true;
    }

/*
    for (int i = 0; i < conn.size(); ++i) {
        auto &p = conn[i];
        cout << "(" << p.first << ", " << p.second << " -> " << cross_counts[i] << ")\n";
    }
    for (auto &p: crosses) {
        cout << "{" << p.first << ", " << p.second << "}\n";
    }
*/

#if 0
    vector<bool> done1(n1, false);
    vector<bool> done2(n1, false);
    auto link = [&](int x1, int x2) {
        int fst, snd;
        vector<bool> &fst_array = done1, &snd_array = done2;
        int fst_n, snd_n;

        if (x1 < x2) {
            fst = x1;
            snd = x2;
            fst_n = n1;
            snd_n = n2;
        } else {
            fst = x2;
            snd = x1;
            fst_array = done2;
            snd_array = done1;
            fst_n = n2;
            snd_n = n1;
        }

        for (int i = fst; i < fst_n; ++i) {
            if (i >= snd) break;
            fst_array[i] = true;
        }

        for (int i = snd; i >= 0; --i) {
            if (i <= fst) break;
            snd_array[i] = true;
        }

        links++;
    };

    for (int i = 0; i < n1; ++i) {
        int search = v1[i];
        if (done1[i]) continue;

        int found_left_idx = -1;
        int found_right_idx = -1;

        int start = min(i, n2-1);
        for (int j = start; j >= 0; --j) {
            if (done2[j]) break;
            if (v2[j] == search) {
                found_left_idx = j;
                break;
            }
        }

        if (i < n2) {
            int start = i;
            for (int j = start; j < n2; ++j) {
                if (done2[j]) break;
                if (v2[j] == search) {
                    found_right_idx = j;
                    break;
                }
            }
        }

        if (found_left_idx < 0 && found_right_idx < 0) continue;
        if (found_left_idx < 0) {
            link(i, found_right_idx);
            continue;
        }
        if (found_right_idx < 0) {
            link(i, found_left_idx);
            continue;
        }

        int left_dist = abs(i - found_left_idx);
        int right_dist = abs(i - found_right_idx);

        int better_idx = (left_dist > right_dist) ? found_right_idx : found_left_idx;
        link(i, better_idx);

        // cout << found_left_idx << ", " << found_right_idx << "\n";
        // break;
    }
#endif

    cout << links << "\n";

    return 0;
}
