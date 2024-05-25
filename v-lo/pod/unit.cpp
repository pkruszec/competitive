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


#define TestPodFile(filename, expected) \
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
        int result = pod(data, cnt, num_parts, max); \
        ExpectEqual(expected, result, "%d"); \
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

    TestPodFile("test1.txt", 11);
    TestPodFile("test2.txt", 8);
    TestPodFile("test3.txt", 15);
    TestPodFile("test4.txt", 159);

    // Expect Less, Greater, etc.
    // Template C++ Versions?
    
    return 0;
}
