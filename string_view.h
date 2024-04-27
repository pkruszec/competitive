#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
    const char *vals;
    size_t count;
} String_View;

#define sv_lit(cstr) (String_View){.vals = (cstr), .count = strlen(cstr)}
#define sv_expand_for_printf(sv) (int)(sv).count, (sv).vals

bool sv_to_uint32_simple(String_View sv, unsigned int base, uint32_t *out_num);
bool sv_to_uint64_simple(String_View sv, unsigned int base, uint64_t *out_num);
bool sv_to_int64_simple(String_View sv, unsigned int base, int64_t *out_num);
bool sv_equal(String_View a, String_View b);
String_View sv_trim_to_next_line(String_View *data);
String_View sv_trim_to_next_char(String_View *data, char c);
String_View sv_trim_char_begin(String_View data, char c);
String_View sv_trim_char_end(String_View data, char c);
const char *sv_end(String_View data);

#endif
