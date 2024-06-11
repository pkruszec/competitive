#include <iostream>
#include <fstream>

/*

3 4 4 6 1 4 4


0 0 0 0 0
0 0 1 0 0
0 0 1 1 0
0 0 1 2 0 <-
1 0 1 1 0
1 0 1 2 0
1 0 1 3 0

*/

int main(int argc, char **argv)
{
#if PRZ1_REDIRECT
    char const *filename = 0;
    if (argc < 2) {
        filename = "test1.txt";
    } else {
        filename = argv[1];
    }
    std::ifstream in(filename);
    std::cin.rdbuf(in.rdbuf());
#endif

    int n, m;
    std::cin >> n >> m;

    int last = n + 1;
    int *arr = new int[n]();

#if 0
    int *ops = new int[m]();

    for (int i = 0; i < m; ++i) {
        std::cin >> ops[i];
        if (ops[i] < last) {
            arr[ops[i] - 1]++;
        }
    }

    //
    //

    int last_max = -1;
    for (int i = n-1; i >= 0; --i) {
        if (ops[i] == last) {
            last_max = i;
            break;
        }
    }

    if (last_max < 0) {
        for (int i = 0; i < n; ++i) {
            std::cout << arr[i] << ' ';
        }
        return 0;
    }

    int max = 0;
    // int idx = -1;
    for (int i = 0; i < last_max; ++i) {
        if (arr[i] > max) {
            max = arr[i];
            // idx = i;
        }
    }

    for (int i = 0; i < n; ++i) {
        arr[i] = max;
    }

    for (int i = last_max+1; i < m; ++i) {
        arr[ops[i]]++;
    }
#endif

#if 0

    int max = 0;

    for (int i = 0; i < m; ++i) {
        int k;
        std::cin >> k;

        if (k == last) {
            // sum += max;
            for (int j = 0; j < n; ++j) {
                arr[j] = max;
            }
        } else {
            arr[k - 1]++;
            if (arr[k - 1] > max) {
                max = arr[k - 1];
            }
        }
    }

#endif

#if 1
    // int *maxes = new int[n]();
    int *ops = new int[m]();

    int max = 0;
    int max_from_button = 0;

    int idx = -1;
    // int sum = 0;

    for (int i = 0; i < m; ++i) {
        int k;
        std::cin >> k;
        ops[i] = k;

        if (k == last) {
            // for (int j = 0; j < n; ++j) {
            //     arr[j] = max;
            // }
            // sum += max;

            idx = i;
        } else {
            // arr[k - 1]++;
            // if (arr[k - 1] > max) {
            //     max = arr[k - 1];
            //     // idx = i;
            //     // maxes[k - 1] = arr[k - 1];
            // }
        }
    }

    for (int i = 0; i < idx; ++i) {
        int k = ops[i];

        if (k == last) {
            // if (i > 0) {
            //     max = arr[ops[i - 1] - 1];
            // }

            // maxes[k-1] = max;
            max_from_button = max;
            if (i < idx-1) arr[ops[i+1] - 1] = max_from_button;
        } else {
            // arr[k-1] = max_from_button + 1;
            arr[k-1]++;

            if (arr[k-1] > max) {
                max = arr[k-1];
            }
        }
    }

    max_from_button = max;

    for (int i = 0; i < n; ++i) {
        arr[i] = max_from_button;
    }

    if (idx < 0) idx = 0;
    if ((idx != m-1)) {
        for (int i = idx+1; i < m; ++i) {
            arr[ops[i] - 1]++;
        }
    }

    // for (int i = 0; i < n; ++i) {
    //     arr[i] += sum;
    // }

#endif

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }

    return 0;
}
