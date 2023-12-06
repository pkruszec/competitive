#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "string_view.h"

bool sv_to_uint32_simple(String_View sv, unsigned int base, uint32_t *out_num)
{
    if (out_num == NULL) return false;
    if (sv.count < 1) return false;
    if (base > 10) return false;
    uint32_t num = 0;
    uint32_t mul = 1;
    
    for (size_t rev_i = 0; rev_i < sv.count; ++rev_i) {
        size_t i = sv.count - rev_i - 1;
        char c = sv.vals[i];
        if (!isdigit(c)) return false;
        int digit = c - '0';
        num += mul * digit;
        mul *= base;
    }
    
    *out_num = num;
    return true;
}

bool sv_to_uint64_simple(String_View sv, unsigned int base, uint64_t *out_num)
{
    if (out_num == NULL) return false;
    if (sv.count < 1) return false;
    if (base > 10) return false;
    uint64_t num = 0;
    uint64_t mul = 1;
    
    for (size_t rev_i = 0; rev_i < sv.count; ++rev_i) {
        size_t i = sv.count - rev_i - 1;
        char c = sv.vals[i];
        if (!isdigit(c)) return false;
        int digit = c - '0';
        num += mul * digit;
        mul *= base;
    }
    
    *out_num = num;
    return true;
}

bool sv_equal(String_View a, String_View b)
{
    if (a.count != b.count) return false;
    
    for (size_t i = 0; i < a.count; ++i) {
        if (a.vals[i] != b.vals[i]) return false;
    }
    
    return true;
}

// NOTE: This function modifies the data string view.
//
// How to iterate:
// 
// String_View data = ...;
// String_View copy = data;
// String_View line = {0};
// while (line.vals < sv_end(copy)) {
//     line = sv_trim_to_next_line(&copy);
//     // process line
//     // ...
// }
//
String_View sv_trim_to_next_line(String_View *data)
{
    String_View line = {0};
    line.vals = data->vals;
    line.count = 0;
    
    while (data->count > 0) {
        if (*(data->vals) == '\r') {
            if (data->count < 2 || *(data->vals + 1) != '\n') {
                // CR
                data->vals++;
                data->count--;
                break;
            } else {
                // CRLF
                data->vals += 2;
                data->count -= 2;
                break;
            }
        }
        else if (*(data->vals) == '\n') {
            // LF
            data->vals++;
            data->count--;
            break;
        }
        
        data->vals++;
        data->count--;
        line.count++;
    }
    
    return line;
}

String_View sv_trim_to_next_char(String_View *data, char c)
{
    String_View line = {0};
    line.vals = data->vals;
    line.count = 0;
    
    while (data->count > 0) {
        if (*(data->vals) == c) {
            data->vals++;
            data->count--;
            break;
        }
        
        data->vals++;
        data->count--;
        line.count++;
    }
    
    return line;
}

String_View sv_trim_char_begin(String_View data, char c)
{
    String_View new_data = data;
    
    for (size_t i = 0; i < data.count; ++i) {
        if (data.vals[i] == c) {
            new_data.vals++;
            new_data.count--;
        } 
        else break;
    }
    
    return new_data;
}

String_View sv_trim_char_end(String_View data, char c)
{
    String_View new_data = data;
    
    for (size_t i = 0; i < data.count; ++i) {
        if (data.vals[data.count-i-1] == c) {
            new_data.count--;
        }
        else break;
    }
    
    return new_data;
}

const char *sv_end(String_View data)
{
    return data.vals + data.count;
}
