#include <limits.h>
#include <stdint.h>

#include <iostream>

#define ABS(x)    ((x) > 0 ? (x) : -(x))
#define SGN(x)    (((x) > 0) - ((x) < 0))
#define MOD(a, b) (((b) + ((a) % (b))) % (b))

struct Node {
    int target;
    int amount;
};

static bool done(Node *nodes, int n)
{
    for (int i = 0; i < n; ++i) {
        if (nodes[i].target != nodes[i].amount) return false;
    }
    return true;
}

static int por_stable(int n, Node *nodes, uint64_t sum_targets, uint64_t sum_amounts)
{
    if (sum_targets != sum_amounts) return -1;

    int transactions = 0;

    while (!done(nodes, n)) {
        for (int i = 0; i < n; ++i) {
            Node *np = &nodes[MOD(i-1, n)];
            Node *nd = &nodes[i];
            Node *nn = &nodes[MOD(i+1, n)];

            int np_diff = np->amount - np->target;
            int nd_diff = nd->amount - nd->target;
            int nn_diff = nn->amount - nn->target;

            if (nd_diff == 0) continue;
            if ((np_diff == 0) && (nn_diff == 0)) continue;

            int nd_np = ABS(ABS(nd_diff) - ABS(np_diff));
            int nd_nn = ABS(ABS(nd_diff) - ABS(nn_diff));
            if (nd_nn < nd_np) {
                nd->amount += nn_diff;
                nn->amount -= nn_diff;

                // std::cerr << i << ": next: " << nn_diff << "\n";
            } else {
                nd->amount += np_diff;
                np->amount -= np_diff;

                // std::cerr << i << ": prev: " << np_diff << "\n";
            }

            transactions += 1;
        }
    }

    return transactions;
}

static int por(int n, Node *nodes, uint64_t sum_targets, uint64_t sum_amounts)
{
    if (sum_targets != sum_amounts) return -1;

    int transactions = 0;

    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            Node *np = &nodes[MOD(i-1, n)];
            Node *nd = &nodes[i];
            Node *nn = &nodes[MOD(i+1, n)];

            int np_diff = np->amount - np->target;
            int nd_diff = nd->amount - nd->target;
            int nn_diff = nn->amount - nn->target;

            if (nd_diff == 0) continue;
            if ((np_diff == 0) && (nn_diff == 0)) continue;

            int nd_np = ABS(ABS(nd_diff) - ABS(np_diff));
            int nd_nn = ABS(ABS(nd_diff) - ABS(nn_diff));
            if (nd_nn < nd_np) {
                nd->amount += nn_diff;
                nn->amount -= nn_diff;

                // std::cerr << i << ": next: " << nn_diff << "\n";
            } else {
                nd->amount += np_diff;
                np->amount -= np_diff;

                // std::cerr << i << ": prev: " << np_diff << "\n";
            }

            transactions += 1;
        }
    }

    return transactions;
}

#if !defined(POR_UNIT_TESTING)
int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    uint64_t sum_targets = 0;
    uint64_t sum_amounts = 0;

    Node *nodes = new Node[n];
    for (int i = 0; i < n; ++i) {
        std::cin >> nodes[i].target >> nodes[i].amount;
        sum_targets += nodes[i].target;
        sum_amounts += nodes[i].amount;
    }

    int result = por(n, nodes, sum_targets, sum_amounts);

    if (result < 0) {
        std::cout << "NIE\n";
        return 0;
    }
    std::cout << result << '\n';

    return 0;
}
#endif