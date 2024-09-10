#include <limits.h>
#include <stdint.h>

#include <iostream>
#include <fstream>

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

static inline int node_diff(Node *node)
{
    return node->amount - node->target;
}

static int node_min_diff_index(int n, Node *nodes)
{
    int min = INT_MAX;
    int best = -1;
    for (int i = 0; i < n; ++i) {
        int diff = node_diff(&nodes[i]);
        int abs = ABS(diff);
        if ((abs < min) && (abs != 0)) {
            min = abs;
            best = i;
        }
    }

    return best;
}

static int por_stable(int n, Node *nodes, uint64_t sum_targets, uint64_t sum_amounts)
{
    if (sum_targets != sum_amounts) return -1;

    int transactions = 0;
    int iterations = 0;

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

static int por_iters(int n, Node *nodes, uint64_t sum_targets, uint64_t sum_amounts)
{
    if (sum_targets != sum_amounts) return -1;

    int transactions = 0;

    // while (!done(nodes, n)) {
    while (true) {
        int iters = 0;

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
            iters += 1;
        }

        if (iters < 1) break;
    }

    return transactions;
}

static int por(int n, Node *nodes, uint64_t sum_targets, uint64_t sum_amounts)
{
    if (sum_targets != sum_amounts) return -1;

    int transactions = 0;

    Node *best = NULL;
    Node *prev = NULL;
    Node *next = NULL;

    //// NEW IDEA ////
    // TODO: Calculate which one has the most to give, and which one has the most to take, and then "move" the money from the former to the latter.

    do {
        int best_idx = node_min_diff_index(n, nodes);
        int prev_idx = MOD(best_idx-1, n);
        int next_idx = MOD(best_idx+1, n);

        if (best_idx < 0) break;

        best = &nodes[best_idx];
        prev = &nodes[prev_idx];
        next = &nodes[next_idx];

        int best_diff = node_diff(best);
        int prev_diff = node_diff(prev);
        int next_diff = node_diff(next);

        int abs_best = ABS(best_diff);
        int best_prev_diff = ABS(abs_best - ABS(prev_diff));
        int best_next_diff = ABS(abs_best - ABS(next_diff));

        if (best_next_diff < best_prev_diff) {
            best->amount += next_diff;
            next->amount -= next_diff;
        } else {
            best->amount += prev_diff;
            prev->amount -= prev_diff;
        }

        // TODO: Find smallest non-negative diff?

        // int diff_diff = fst_diff - snd_diff;

        // if (diff_diff > 0) {
        //     best.first->amount -= fst_diff;
        //     best.second->amount += fst_diff;
        // } else {
        //     best.second->amount -= snd_diff;
        //     best.first->amount += snd_diff;
        // }

        transactions++;

    } while (true);

    return transactions;
}

#if !defined(POR_UNIT_TESTING)
int main(int argc, char **argv)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    #if POR_REDIRECT
    char const *filename = 0;
    if (argc < 2) {
        filename = "./tests/test1.txt";
    } else {
        filename = argv[1];
    }
    std::ifstream in(filename);
    std::cin.rdbuf(in.rdbuf());
    #endif

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

    // int result = por_stable(n, nodes, sum_targets, sum_amounts);
    int result = por(n, nodes, sum_targets, sum_amounts);

    if (result < 0) {
        std::cout << "NIE\n";
        return 0;
    }
    std::cout << result << '\n';

    return 0;
}
#endif