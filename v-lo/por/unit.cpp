#include <string.h>

#include <fstream>

#define UNIT_BENCH_INDENT 25
#define UNIT_IMPLEMENTATION
#include "unit.h"

#define POR_UNIT_TESTING
#include "por.cpp"

struct Test {
    const char *path;
};

struct Test_Data {
    uint64_t sum_targets;
    uint64_t sum_amounts;
    int expected;
    int count;
    Node *nodes;
};

#define ARRAY_LEN(a) (sizeof(a)/sizeof((a)[0]))

#define PATH_DIR "./tests/"
#define PATH_EXT ".txt"

#define TEST(x) Test{PATH_DIR x PATH_EXT}

static Test tests_man[] = {
    TEST("test_man_1"),
    TEST("test_man_2"),
    TEST("test_man_3"),
};

static Test tests[] = {
    TEST("test_man_1"),
    TEST("test_man_2"),
    TEST("test_man_3"),
};

static void td_open_and_parse(const char *path, Test_Data *td)
{
    memset(td, 0, sizeof(*td));
    std::ifstream in(path);

    in >> td->expected >> td->count;

    td->nodes = new Node[td->count];
    for (int i = 0; i < td->count; ++i) {
        in >> td->nodes[i].target >> td->nodes[i].amount;
        td->sum_targets += td->nodes[i].target;
        td->sum_amounts += td->nodes[i].amount;
    }
}

#define RUN_FN(fn, td) fn((td)->count, (td)->nodes, (td)->sum_targets, (td)->sum_amounts)

#define RUN_TEST(test, fn) \
    do { \
        printf("running test %s\n", (test)->path); \
        Test_Data td; \
        td_open_and_parse((test)->path, &td); \
        int res = RUN_FN(fn, &td); \
        ExpectEqual(res, td.expected, "%d"); \
        delete[] td.nodes; \
    } while (0)

#define RUN_TESTS(arr, fn) \
    do { \
        printf("TEST GROUP: %s, %s\n", #arr, #fn); \
        for (size_t i = 0; i < ARRAY_LEN(arr); ++i) { \
            RUN_TEST(&arr[i], fn); \
        } \
        printf("\n"); \
    } while (0)

#define COUNT 50000

#define RUN_BENCHES(bench, arr, fn) \
    do { \
        Test_Data td; \
        for (size_t i = 0; i < ARRAY_LEN(arr); ++i) { \
            td_open_and_parse((arr)[i].path, &td); \
            unit_bench_test(bench, (arr)[i].path); \
            for (size_t k = 0; k < COUNT; ++k) { \
                int res = RUN_FN(fn, &td); \
            } \
            unit_bench_end_test(bench); \
            delete[] td.nodes; \
        } \
    } while (0)

int main(int argc, char **argv)
{
    if (argc > 1) {
        const char *path = argv[1];
        Test_Data td;
        td_open_and_parse(path, &td);
        int res = RUN_FN(por_stable, &td);
        fprintf(stderr, "%zu, %zu %zu\n", td.count, td.sum_targets, td.sum_amounts);
        printf("%d\n", res);
        return 0;
    }

    RUN_TESTS(tests_man, por_stable);
    RUN_TESTS(tests, por);

    Unit_Bench bench;
    unit_bench_init(&bench);

    {
        unit_bench_group(&bench, "por_stable");
        RUN_BENCHES(&bench, tests, por_stable);
        unit_bench_end_group(&bench);
    }

    {
        unit_bench_group(&bench, "por");
        RUN_BENCHES(&bench, tests, por);
        unit_bench_end_group(&bench);
    }

    unit_bench_print_results_and_reset(&bench);

    return 0;
}
