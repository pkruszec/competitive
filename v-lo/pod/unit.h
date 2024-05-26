/* unit.h - simple unit testing & benchmarking library

   Do this:
      #define UNIT_IMPLEMENTATION
   before you include this file in *one* C or C++ file to create the implementation.

   REPLACEMENTS
      UnitAlloc, UnitRealloc, UnitFree - memory allocation API

   CONFIGURATION:
      UNIT_LOG_PASSED - if defined, logs tests that passed
*/

#ifndef UNIT_H
#define UNIT_H

#ifdef __cplusplus
extern "C" {
#endif

//
// Utilities
//

#ifndef UnitArrayCount
# define UnitArrayCount(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

#ifndef UNITDEF
# define UNITDEF static
#endif

#ifndef unit_int64
# ifdef _MSC_VER
#  define unit_int64 signed __int64
# else
#  define unit_int64 signed long long
# endif
#endif

#ifndef UnitMemset
# define UnitMemset(ptr, value, size) unit__memset(ptr, value, size)
#endif

#ifndef UnitMax
# define UnitMax(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef UnitStringsEqual
# define UnitStringsEqual(a, b) unit__strings_equal(a, b)
#endif

#ifndef UnitAlloc
# include <stdlib.h>
# define UnitAlloc(size)        malloc(size)
# define UnitRealloc(ptr, size) realloc(ptr, size)
# define UnitFree(ptr)          free(ptr)
#endif

//
// Logging
//

#ifndef UnitLog // Must support printf formatting.
# include <stdio.h>
# define UnitLog(...) fprintf(stderr, __VA_ARGS__)
#endif

#ifndef UNIT_TEST_PASSED_STRING
# define UNIT_TEST_PASSED_STRING "TEST PASSED: "
#endif
#ifndef UNIT_TEST_FAILED_STRING
# define UNIT_TEST_FAILED_STRING "TEST FAILED: "
#endif

#ifdef UNIT_LOG_PASSED
# define UnitLogPassed(...) UnitLog(UNIT_TEST_PASSED_STRING __VA_ARGS__)
#else
# define UnitLogPassed(...)
#endif

#define UnitLogFailed(...) UnitLog(UNIT_TEST_FAILED_STRING __VA_ARGS__)

//
// Benchmarking
// Allocates memory!
//

#ifndef UNIT_BENCH_INIT_ARENA_SIZE
# define UNIT_BENCH_INIT_ARENA_SIZE 4096
#endif

#ifndef UNIT_BENCH_PERF_COUNT_DIVISOR
# define UNIT_BENCH_PERF_COUNT_DIVISOR 1000
#endif

#ifndef UnitBenchPerfCount
# define UnitBenchPerfCount() __rdtsc()
#endif

typedef struct {
    const char *name;
    unit_int64 new_value;
    unit_int64 first_value;
} Unit_Bench_Result;

typedef struct {
    const char *name;
    unit_int64 result;
} Unit_Bench_Test;

typedef struct {
    const char *name;
    unsigned int test_count;
    int test_started;
} Unit_Bench_Group;

#define UNIT_BENCH_GROUP_HEADER_SIZE sizeof(Unit_Bench_Group)

typedef struct {
    unsigned char *arena;
    unsigned int arena_size;
    unsigned int arena_pos;

    Unit_Bench_Group *current_group;
    Unit_Bench_Group *first_group;
    unsigned int group_count;

    Unit_Bench_Result *results;
    unsigned int result_count;
} Unit_Bench;

UNITDEF void unit_bench_init(Unit_Bench *b);
UNITDEF void unit_bench_destroy(Unit_Bench *b);
UNITDEF void unit_bench_reset(Unit_Bench *b);
UNITDEF void unit_bench_group(Unit_Bench *b, const char *name);
UNITDEF void unit_bench_end_group(Unit_Bench *b);
UNITDEF void unit_bench_test(Unit_Bench *b, const char *name);
UNITDEF void unit_bench_end_test(Unit_Bench *b);
UNITDEF void unit_bench_print_results_and_reset(Unit_Bench *b);

//
// Expects
//

// TODO: Namespace this stuff!

#define Expect(x) \
    do { \
        if (x) { \
            UnitLogPassed(#x "\n"); \
        } else { \
            UnitLogFailed("Expected to be true: " #x "\n"); \
        } \
    } while (0)

#define ExpectEqual(exp, got, fmt) \
    do { \
        if ((exp) == (got)) { \
            UnitLogPassed(#got " == " #exp " (" fmt ")" "\n", exp); \
        } else { \
            UnitLogFailed("Expected " fmt ", got " fmt "\n", exp, got); \
        } \
    } while (0)

#endif /* UNIT_H */

#ifdef UNIT_IMPLEMENTATION

UNITDEF void *unit__memset(void *ptr, unsigned char value, int size)
{
    unsigned char *pos = (unsigned char *)ptr;
    while (size >= 0) {
        *pos = value;
        pos++;
        size--;
    }
    return ptr;
}

UNITDEF int unit__strings_equal(const char *a, const char *b)
{
    while (1) {
        if ((*a == 0) && (*b == 0)) return 1;
        else if ((*a) == 0 || (*b == 0)) return 0;

        if ((*a) != (*b)) return 0;

        a++;
        b++;
    }

    return 0;
}

UNITDEF void unit_bench_init(Unit_Bench *b)
{
    UnitMemset(b, 0, sizeof(*b));
    b->arena_size = UNIT_BENCH_INIT_ARENA_SIZE;
    b->arena = (unsigned char *)UnitAlloc(b->arena_size);
}

// NOTE: always zeroes out memory
UNITDEF void *unit__bench_alloc(Unit_Bench *b, unsigned int size)
{
    if (b->arena_pos + size > b->arena_size) {
        unsigned int new_size = b->arena_size + UnitMax(b->arena_size, size);
        void *new_ptr = UnitRealloc(b->arena, new_size);
        if (!new_ptr) return 0;
        b->arena = (unsigned char *)new_ptr;
        b->arena_size = new_size;
    }

    void *ptr = b->arena + b->arena_pos;
    b->arena_pos += size;
    UnitMemset(ptr, 0, size);
    return ptr;
}

UNITDEF void unit_bench_destroy(Unit_Bench *b)
{
    UnitFree(b->arena);
}

UNITDEF void unit_bench_reset(Unit_Bench *b)
{
    b->arena_pos = 0;
}

UNITDEF void unit_bench_group(Unit_Bench *b, const char *name)
{
    // NOTE: Pointless right now, but we might add stuff into end_group()
    if (b->current_group)
        unit_bench_end_group(b);

    b->current_group = (Unit_Bench_Group *)unit__bench_alloc(b, sizeof(*b->current_group));
    b->current_group->name = name;
    b->group_count++;

    if (!b->first_group)
        b->first_group = b->current_group;
}

UNITDEF void unit_bench_end_group(Unit_Bench *b)
{
    b->current_group = 0;
}

// TODO: Add an iteration count to further differentiate the tests
UNITDEF void unit_bench_test(Unit_Bench *b, const char *name)
{
    if (!b->current_group) {
        // TODO: Should we automatically add an anonymous group here?
        return;
    }

    if (b->current_group->test_started) {
        unit_bench_end_test(b);
    }

    b->current_group->test_started = 1;

    Unit_Bench_Test *test = (Unit_Bench_Test *)unit__bench_alloc(b, sizeof(*test));
    test->name = name;
    test->result = UnitBenchPerfCount();
    b->current_group->test_count++;
}

UNITDEF void unit_bench_end_test(Unit_Bench *b)
{
    if (!b->current_group) {
        return;
    }

    Unit_Bench_Test *tests = (Unit_Bench_Test *)((char *)b->current_group + UNIT_BENCH_GROUP_HEADER_SIZE);
    Unit_Bench_Test *test = &tests[b->current_group->test_count - 1];
    unit_int64 last_time = test->result;
    unit_int64 result = (UnitBenchPerfCount() - last_time) / UNIT_BENCH_PERF_COUNT_DIVISOR;
    test->result = result;

    b->current_group->test_started = 0;
}

UNITDEF Unit_Bench_Result *unit__bench_search_result(Unit_Bench *b, const char *name)
{
    for (unsigned int i = 0; i < b->result_count; ++i) {
        Unit_Bench_Result *res = &b->results[i];
        if (UnitStringsEqual(name, res->name)) return res;
    }

    return 0;
}

UNITDEF void unit_bench_print_results_and_reset(Unit_Bench *b)
{
    UnitLog("\nBENCHMARK\n");

    int indent = 20;

    unsigned char *pos = (unsigned char *)b->first_group;
    for (unsigned int i = 0; i < b->group_count; ++i) {
        Unit_Bench_Group *group = (Unit_Bench_Group *)pos;
        pos += UNIT_BENCH_GROUP_HEADER_SIZE;

        UnitLog(" %s\n", group->name);
        UnitLog(
            "  %*s | %*s | %*s\n",
            indent, "Name",
            indent, "Count",
            indent, "Comparison w/ Prev"
        );

        for (unsigned int j = 0; j < group->test_count; ++j) {

            Unit_Bench_Test *test = (Unit_Bench_Test *)pos;
            Unit_Bench_Result *searched = unit__bench_search_result(b, test->name);

            double mult = 1.0;
            unit_int64 value = 0;

            if (searched) {
                Unit_Bench_Result *res = searched;
                res->new_value = test->result;
                mult = (double)res->first_value / (double)res->new_value;
                value = res->new_value;
            } else {
                // NOTE: This relies on the arena's contiguousness.
                // This disallows any allocations in between.
                Unit_Bench_Result *res = (Unit_Bench_Result *)unit__bench_alloc(b, sizeof(*res));
                if (!b->results) b->results = res;

                res->name = test->name;
                res->first_value = test->result;
                res->new_value = res->first_value;
                value = res->new_value;
                b->result_count++;
            }

            UnitLog(
                "  %*s | %*lld | %*.4f\n", 
                indent, test->name,
                indent, value,
                indent, mult
            );

            pos += sizeof(Unit_Bench_Test);
        }
    }

    unit_bench_reset(b);
}

#endif /* UNIT_IMPLEMENTATION */

#ifdef __cplusplus
}
#endif