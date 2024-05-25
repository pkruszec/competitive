#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

// #define UNIT_LOG_PASSED
#define UNIT_IMPLEMENTATION
#include "unit.h"

#define UNIT_TESTING
#include "pod.cpp"

static int get_max(int *data, int count)
{
    int max = 0;
    for (int i = 0; i < count; ++i) {
        if (data[i] > max) max = data[i];
    }
    return max;
}

struct Read_File_Result {
    char *ptr;
    intptr_t size;
};

//
// If the file couldn't be read, size == -1
static Read_File_Result read_entire_text_file(const char *path)
{
    Read_File_Result result = {};
    result.size = -1;

    FILE *f = fopen(path, "r");

    // NOTE: This code structure is intentional!
    if (f) {
        fseek(f, 0, SEEK_END);
        long size = ftell(f);
        fseek(f, 0, SEEK_SET);

        if (size) {
            size--;
            char *ptr = (char *)malloc(size + 1);
            if (ptr) {
                fread(ptr, 1, size, f);
                result.size = size;
                result.ptr = ptr;
                ptr[result.size] = 0;
            }
        }

        fclose(f);
    }

    return result;
}

// #define TestPodSimple(num_parts, expected, ...) \
//     do { \
//         int data[] = {__VA_ARGS__}; \
//         size_t cnt = UnitArrayCount(data); \
//         int result = pod(data, cnt, num_parts, get_max(data, cnt)); \
//         ExpectEqual(expected, result, "%d"); \
//     } while (0)

typedef struct {
    int *data;
    int cnt;
    int num_parts;
    int max;
    unit_int64 sum;
} Pod_Input;

#define PodReadFile(filename, input) \
    do { \
        Read_File_Result file = read_entire_text_file(filename); \
        if (file.size < 0) return 1; \
        int pos = 0; \
        int cnt = 0; \
        int num_parts = 0; \
        unit_int64 sum = 0; \
        sscanf(file.ptr, "%d%d%n", &cnt, &num_parts, &pos); \
        file.ptr += pos; \
        int max = -1; \
        int *data = (int *)malloc(sizeof(*data) * cnt); \
        for (int i = 0; i < cnt; ++i) { \
            sscanf(file.ptr, "%d%n", &data[i], &pos); \
            if (data[i] > max) max = data[i]; \
            sum += data[i]; \
            file.ptr += pos; \
        } \
        (input)->data = data; \
        (input)->cnt = cnt; \
        (input)->num_parts = num_parts; \
        (input)->max = max; \
        (input)->sum = sum; \
    } while (0)

#define TestFile(filename, expected, fn) \
    do { \
        Pod_Input input = {}; \
        PodReadFile(filename, &input); \
        int result = fn(input.data, input.cnt, input.num_parts, input.max, input.sum); \
        ExpectEqual(expected, result, "%d"); \
        free(input.data); \
    } while (0)

#define N_SMALL 1000
#define N_BIG   10

#define BenchFile(bench, filename, fn, count) \
    do { \
        Pod_Input input = {}; \
        PodReadFile(filename, &input); \
        unit_bench_test(bench, filename); \
        for (int i = 0; i < (count); ++i) { \
            int result = fn(input.data, input.cnt, input.num_parts, input.max, input.sum); \
        } \
        unit_bench_end_test(bench); \
        free(input.data); \
    } while (0)

#define TestAndBenchSet \
    X("test1.txt", 11, N_SMALL) \
    X("test2.txt", 8, N_SMALL) \
    X("test3.txt", 15, N_SMALL) \
    X("test4.txt", 159, N_SMALL) \
    X("test_1000_12_rng.txt", 8573, N_BIG)

int main(void)
{
    UnitLog("\nTEST GROUP: pod\n\n");
#define X(f, e, n) TestFile(f, e, pod);
    TestAndBenchSet
#undef X

    UnitLog("\nTEST GROUP: pod_rtl\n\n");
#define X(f, e, n) TestFile(f, e, pod_rtl);
    TestAndBenchSet
#undef X

    UnitLog("\nTEST GROUP: pod_bigger_first_s\n\n");
#define X(f, e, n) TestFile(f, e, pod_bigger_first_s);
    TestAndBenchSet
#undef X

    Unit_Bench bench;
    unit_bench_init(&bench);

    //
    // pod
    //

    unit_bench_group(&bench, "pod");
#define X(f, e, n) BenchFile(&bench, f, pod, n);
    TestAndBenchSet
#undef X
    unit_bench_end_group(&bench);

    //
    // pod_rtl
    //

    unit_bench_group(&bench, "pod_rtl");
#define X(f, e, n) BenchFile(&bench, f, pod_rtl, n);
    TestAndBenchSet
#undef X
    unit_bench_end_group(&bench);

    //
    // pod_bigger_first_s
    //

    unit_bench_group(&bench, "pod_bigger_first_s");
#define X(f, e, n) BenchFile(&bench, f, pod_bigger_first_s, n);
    TestAndBenchSet
#undef X
    unit_bench_end_group(&bench);

    unit_bench_print_results_and_reset(&bench);

    // Expect Less, Greater, etc.
    // Template C++ Versions?
    
    return 0;
}
