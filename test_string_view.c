#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "string_view.h"

#define CHAR_ARRAY_LEN(arr) ((sizeof(arr) - sizeof((arr)[0])) / sizeof((arr)[0]))

#define test_assert(cond) \
do { \
if (!(cond)) { \
fprintf(stderr, "--- TEST FAILED: %-40s: " #cond " at " __FILE__ ", line %d\n", __func__, __LINE__); \
exit(1); \
} else { \
fprintf(stderr, "TEST PASSED: %-40s: " #cond "\n", __func__); \
} \
} while (0) 


static void test_sv_lit(void)
{
    String_View sv;
    
    char a[] = "hello";
    char b[] = "";
    
#define local_test(arr) \
do { \
sv = sv_lit(arr);\
test_assert(sv.count == CHAR_ARRAY_LEN(arr));\
} while (0)
    
    local_test(a);
    local_test(b);
    
#undef local_test
    
}


static void test_sv_trim_char_begin(void)
{
    String_View sv;
    
#define local_test(orig, c, exp) \
do { \
sv = sv_lit(orig); \
sv = sv_trim_char_begin(sv, c); \
test_assert(sv_equal(sv, sv_lit(exp))); \
} while (0)
    
    local_test(" test", ' ', "test");
    local_test("      eee", ' ', "eee");
    local_test("      ", ' ', "");
    local_test("", ' ', "");
    local_test("test", ' ', "test");
    
#undef local_test
}

static void test_sv_trim_char_end(void)
{
    String_View sv;
    
#define local_test(orig, c, exp) \
do { \
sv = sv_lit(orig); \
sv = sv_trim_char_end(sv, c); \
test_assert(sv_equal(sv, sv_lit(exp))); \
} while (0)
    
    local_test("test ", ' ', "test");
    local_test("           ", ' ', "");
    local_test("test", ' ', "test");
    local_test("test\n\n", '\n', "test");
    local_test("", ' ', "");
    
#undef local_test
}

void test_sv_equal(void)
{
    String_View a, b;
    
#define local_test(s0, s1, val) \
do { \
a = sv_lit(s0);\
b = sv_lit(s1);\
test_assert(sv_equal(a, b) == (val));\
} while (0)
    
    local_test("a", "b", false);
    local_test("", "", true);
    local_test("hello", "hello", true);
    local_test("hell", "hello", false);
    local_test("hello", "he", false);
    
#undef local_test
}

int main(void)
{
    test_sv_lit();
    test_sv_trim_char_begin();
    test_sv_trim_char_end();
    test_sv_equal();
    
    return 0;
}