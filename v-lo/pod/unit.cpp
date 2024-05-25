#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>

#define UNIT_LOG_PASSED
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

#define TestPodSimple(num_parts, expected, ...) \
    do { \
        int data[] = {__VA_ARGS__}; \
        size_t cnt = UnitArrayCount(data); \
        int result = pod(data, cnt, num_parts, get_max(data, cnt)); \
        ExpectEqual(expected, result, "%d"); \
    } while (0)

typedef struct {
    int *data;
    int cnt;
    int num_parts;
    int max;
} Pod_Input;

#define PodReadFile(filename, input) \
    do { \
        Read_File_Result file = read_entire_text_file(filename); \
        if (file.size < 0) return 1; \
        int pos = 0; \
        int cnt = 0; \
        int num_parts = 0; \
        sscanf(file.ptr, "%d%d%n", &cnt, &num_parts, &pos); \
        file.ptr += pos; \
        int max = -1; \
        int *data = (int *)malloc(sizeof(*data) * cnt); \
        for (int i = 0; i < cnt; ++i) { \
            sscanf(file.ptr, "%d%n", &data[i], &pos); \
            if (data[i] > max) max = data[i]; \
            file.ptr += pos; \
        } \
        (input)->data = data; \
        (input)->cnt = cnt; \
        (input)->num_parts = num_parts; \
        (input)->max = max; \
    } while (0)

#define TestPodFile(filename, expected) \
    do { \
        Pod_Input input = {}; \
        PodReadFile(filename, &input); \
        int result = pod(input.data, input.cnt, input.num_parts, input.max); \
        ExpectEqual(expected, result, "%d"); \
        free(input.data); \
    } while (0)

#define N 1000

#define BenchPodFile(bench, filename, count) \
    do { \
        Pod_Input input = {}; \
        PodReadFile(filename, &input); \
        unit_bench_test(bench, filename); \
        for (int i = 0; i < (count); ++i) { \
            int result = pod(input.data, input.cnt, input.num_parts, input.max); \
        } \
        unit_bench_end_test(bench); \
        free(input.data); \
    } while (0)

int main(void)
{
    /*
    TestPodSimple(
        4, 11,
        1, 5, 3, 2, 4, 7, 1, 2, 8, 6
    );

    TestPodSimple(
        6, 8,
        4, 2, 8, 3, 5, 6, 1, 7
    );

    TestPodSimple(
        4, 15,
        8, 5, 10, 1, 3, 4, 9, 7, 6, 2
    );
    */

    // TODO: Make a benchmarking system that keeps track of groups and tests
    // e.g.
    /*

    Unit_Bench bench;
    unit_bench_init(&bench);

    unit_bench_group(&bench, "pod");

    // This could be abstracted into a user macro.
    unit_bench_test(&bench, "test1.txt");
    TestPodFile("test1.txt", 11);
    unit_bench_end_test(&bench);

    unit_bench_test(&bench, "test1.txt");
    TestPodFile("test2.txt", 8);
    unit_bench_end_test(&bench);

    unit_bench_end_group(&bench);

    unit_bench_print_results(&bench);
    unit_bench_reset(&bench);

    */

    TestPodFile("test1.txt", 11);
    TestPodFile("test2.txt", 8);
    TestPodFile("test3.txt", 15);
    TestPodFile("test4.txt", 159);

    Unit_Bench bench;
    unit_bench_init(&bench);

    unit_bench_group(&bench, "pod");

    BenchPodFile(&bench, "test1.txt", N);
    BenchPodFile(&bench, "test2.txt", N);
    BenchPodFile(&bench, "test3.txt", N);
    BenchPodFile(&bench, "test4.txt", N);

    unit_bench_end_group(&bench);

    unit_bench_group(&bench, "pod2");

    BenchPodFile(&bench, "test1.txt", N);
    BenchPodFile(&bench, "test2.txt", N);
    BenchPodFile(&bench, "test3.txt", N);
    BenchPodFile(&bench, "test4.txt", N);

    unit_bench_end_group(&bench);

    unit_bench_print_results_and_reset(&bench);

    // Expect Less, Greater, etc.
    // Template C++ Versions?
    
    return 0;
}
