#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

static bool check_count(int *items, int len, int k, int limit)
{
    int count = 1;
    int sum = 0;
    for (int i = 0; i < len; ++i) {
        int x = items[i];
        sum += x;
        if (sum > limit) {
            sum = x;
            count++;
        }
    }
    return count <= k;
}

static int pod_binary(int *items, int count, int k, int max, int64_t sum)
{
    int lower = max;
    int upper = sum;
    while (lower < upper) {
        int mid = lower + (upper-lower) / 2;
        if (check_count(items, count, k, mid)) {
            upper = mid;
        } else {
            lower = mid + 1;
        }
    }
    return lower;
}

#ifndef UNIT_TESTING
int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int count, num_parts;
    std::cin >> count >> num_parts;

    int max = 0;
    int64_t sum = 0;

    int *items = new int[count];

    for (int i = 0; i < count; i++) {
        std::cin >> items[i];
        if (items[i] > max) max = items[i];
        sum += items[i];
    }

    int result = pod_binary(items, count, num_parts, max, sum);
    std::cout << result;
    return 0;
}
#endif // UNIT_TESTING
