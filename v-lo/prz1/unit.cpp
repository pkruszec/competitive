#include <stdio.h>
#include <string.h>

#include <fstream>

#define UNIT_IMPLEMENTATION
#include "unit.h"

#define UNIT_TESTING 1
#include "prz1.cpp"

#define ARRAY_LEN(a) (sizeof(a)/sizeof((a)[0]))

struct Test {
    const char *input_name;
    const char *exp_name;
};

#define TEST_DIR "./tests/"
#define TEST_EXP_EXT ".exp.txt"
#define TEST_INP_EXT ".txt"

#define TEST(stem) Test{TEST_DIR stem TEST_INP_EXT, TEST_DIR stem TEST_EXP_EXT}

static Test tests_stable[] = {
    TEST("test1"),
    TEST("test2"),
    TEST("test3"),
};

static Test tests[] = {
    TEST("test1"),
    TEST("test2"),
    TEST("test3"),
    TEST("testpy_1"),
    TEST("testpy_2"),
    TEST("testpy_3"),
    TEST("testpy_4"),
    TEST("testpy_5"),
    TEST("testpy_6"),
    TEST("testpy_7"),
    TEST("testpy_8"),
    TEST("testpy_9"),
    TEST("testpy_10"),
    TEST("testpy_11"),
    TEST("testpy_12"),
    TEST("testpy_13"),
    TEST("testpy_14"),
    TEST("testpy_15"),
    TEST("testpy_16"),
    TEST("testpy_17"),
    TEST("testpy_18"),
    TEST("testpy_19"),
    TEST("testpy_20"),
};

#define RUN_TEST(test, fn) \
    do { \
        printf("running test %s\n", (test)->input_name); \
 \
        std::ifstream inp_stm((test)->input_name); \
 \
        int n, m; \
        inp_stm >> n >> m; \
 \
        int *exp = new int[n]; \
        std::ifstream exp_stm((test)->exp_name); \
        for (int i = 0; i < n; ++i) { \
            exp_stm >> exp[i]; \
        } \
 \
        int *arr = fn(n, m, inp_stm); \
        bool eq = true; \
        for (int i = 0; i < n; ++i) { \
            if (arr[i] != exp[i]) { \
                eq = false; \
                break; \
            } \
        } \
 \
        Expect(eq); \
        if (!eq) { \
            printf("EXP:\n"); \
            for (int i = 0; i < n; ++i) { \
                printf("%d ", exp[i]); \
            } \
            printf("\n"); \
 \
            printf("ARR:\n"); \
            for (int i = 0; i < n; ++i) { \
                printf("%d ", arr[i]); \
            } \
            printf("\n"); \
        } \
        delete[] arr;\
        delete[] exp;\
    } while (0)

#define RUN_TESTS(arr, fn) \
    do { \
        printf("TEST GROUP: %s, %s\n", #arr, #fn); \
        for (size_t i = 0; i < ARRAY_LEN(arr); ++i) { \
            RUN_TEST(&arr[i], fn); \
        } \
        printf("\n"); \
    } while (0)

static void run_stable(const char *path)
{
    std::ifstream in(path);

    int n, m;
    in >> n >> m;

    int *arr = prz1_stable(n, m, in);
    for (int i = 0; i < n; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    delete[] arr;
}

int main(int argc, char **argv)
{

    if (argc > 1) {
        char *action = argv[1];

        if (strcmp(action, "stable") == 0) {
            if (argc < 3) return 1;

            char *path = argv[2];

            run_stable(path);
        }
        return 0;
    }

    // Stable Check
    RUN_TESTS(tests_stable, prz1_stable);

    RUN_TESTS(tests, prz1_last_max_op);

    return 0;
}
