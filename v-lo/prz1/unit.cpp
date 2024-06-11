#include <fstream>
#include <stdio.h>

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
    } while (0)

#define RUN_TESTS(arr, fn) \
    do { \
        printf("TEST GROUP: %s, %s\n", #arr, #fn); \
        for (size_t i = 0; i < ARRAY_LEN(arr); ++i) { \
            RUN_TEST(&arr[i], fn); \
        } \
        printf("\n"); \
    } while (0)

int main(void)
{
    // Stable Check
    RUN_TESTS(tests_stable, prz1_stable);

    RUN_TESTS(tests, prz1_last_max_op);

    return 0;
}
