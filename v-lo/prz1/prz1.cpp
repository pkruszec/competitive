#include <iostream>
#include <fstream>

static int *prz1_stable(int n, int m, std::istream &input)
{
    int last = n + 1;
    int *arr = new int[n]();

    int max = 0;

    for (int i = 0; i < m; ++i) {
        int k;
        input >> k;

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

    return arr;
}

static int *prz1_last_max_op(int n, int m, std::istream &input)
{
    int last = n + 1;
    int *arr = new int[n]();
    int *ops = new int[m];

    int max = 0;
    int max_from_button = 0;

    int idx = -1;
    bool idx_set = false;

    for (int i = 0; i < m; ++i) {
        int k;
        input >> k;
        ops[i] = k;

        if (k == last) {
            idx = i;
        }
    }

    if (idx < 0) idx = 0;
    else idx_set = true;

    for (int i = 0; i < idx; ++i) {
        int k = ops[i];

        if (k == last) {
            max_from_button = max;
        } else {
            if (arr[k-1] > max_from_button) {
                arr[k-1]++;
            } else {
                arr[k-1] = max_from_button + 1;
            }            

            if (arr[k-1] > max) {
                max = arr[k-1];
            }
        }
    }

    max_from_button = max;

    if (idx_set) {
        for (int i = 0; i < n; ++i) {
            arr[i] = max_from_button;
        }
    }

    if (!idx_set) idx = 0;
    else idx++;

    for (int i = idx; i < m; ++i) {
        arr[ops[i] - 1]++;
    }

    // if ((idx != m-1)) { 
    // }

#if UNIT_TESTING
    delete[] ops;
#endif
    return arr;
}

#if !UNIT_TESTING
int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

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

#if 0
    int *arr = prz1_stable(n, m, std::cin);
#else
    int *arr = prz1_last_max_op(n, m, std::cin);
#endif

    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << ' ';
    }

    return 0;
}
#endif // UNIT_TESTING