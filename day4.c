#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
    const char *vals;
    size_t count;
} String_View;

#define sv_lit(cstr) (String_View){.vals = (cstr), .count = strlen(cstr)}
#define sv_expand_for_printf(sv) (sv).count, (sv).vals

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
// while (line.data < copy.data+copy.count) {
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

const char *sv_end(String_View data)
{
    return data.vals + data.count;
}

#define LINE_MAX 256
#define WINNING_MAX 64
#define COPIES_MAX 256

void sum_copies(size_t id, uint32_t *copies, size_t *copy_sum)
{
    if (copies[id] == 0) return;
    
    *copy_sum += copies[id];
    for (size_t i = id+1; i <= id+copies[id]; ++i) {
        sum_copies(i, copies, copy_sum);
    }
}

int main(void)
{
    const String_View prefix = sv_lit("Card ");
    
    uint32_t winning_numbers[WINNING_MAX];
    // uint32_t your_numbers[YOUR_MAX];
    size_t winning_count = 0;
    // size_t your_count = 0;
    
    uint32_t copies[COPIES_MAX] = {0};
    
    size_t sum = 0;
    size_t copy_sum = 0;
    
    char line[LINE_MAX];
    while (fgets(line, LINE_MAX, stdin)) {
        size_t line_len = strlen(line);
        String_View line_sv = {
            .count = line_len,
            .vals = line
        };
        
        if (line_sv.vals[line_sv.count - 1] == '\n') line_sv.count--;
        
        line_sv.vals += prefix.count;
        line_sv.count -= prefix.count;
        
        String_View line_sv_without_id = line_sv;
        String_View id_sv = sv_trim_char_begin(sv_trim_to_next_char(&line_sv_without_id, ':'), ' ');
        
        uint32_t id = 0;
        if (!sv_to_uint32_simple(id_sv, 10, &id)) return 1;
        
        String_View your_numbers_sv = line_sv_without_id;
        String_View winning_numbers_sv = sv_trim_to_next_char(&your_numbers_sv, '|');
        
        your_numbers_sv = sv_trim_char_begin(your_numbers_sv, ' ');
        winning_numbers_sv = sv_trim_char_begin(winning_numbers_sv, ' ');
        
        String_View copy;
        String_View number_sv = {0};
        uint32_t number;
        
        fprintf(stderr, "%.*s\n", sv_expand_for_printf(line_sv));
        
        winning_count = 0;
        
        copy = winning_numbers_sv;
        while (number_sv.vals < sv_end(copy)) {
            number_sv = sv_trim_to_next_char(&copy, ' ');
            if (number_sv.count < 1) continue;
            if (!sv_to_uint32_simple(number_sv, 10, &number)) return 1;
            
            if (winning_count >= WINNING_MAX) return 2;
            winning_numbers[winning_count++] = number;
        }
        
        size_t amount = 0;
        size_t score = 0;
        
        copy = your_numbers_sv;
        while (number_sv.vals < sv_end(copy)) {
            number_sv = sv_trim_to_next_char(&copy, ' ');
            if (number_sv.count < 1) continue;
            if (!sv_to_uint32_simple(number_sv, 10, &number)) return 1;
            
            for (size_t i = 0; i < winning_count; ++i) {
                if (winning_numbers[i] == number) {
                    ++amount;
                    score = (score == 0) ? 1 : score*2;
                }
            }
        }
        
        sum += score;
        
        // copies[id] = amount;
        
        copies[id]++;
#if 1
        for (size_t i = id+1; i < id+amount+1; ++i) {
            if (i >= COPIES_MAX) return 3;
            copies[i] += copies[id];
            // copies[i] *= 2;
            // copies[i] *= ;
            // copies[i] *= 2;
            // copies[i] = (copies[i] == 0) ? 1 : (copies[i]*2);
            fprintf(stderr, "%zu (copies = %u): %zu\n", id, copies[id], i);
        }
#endif
        
        
    }
    
    for (size_t i = 0; i < COPIES_MAX; ++i) {
        // sum_copies(i, copies, &copy_sum);
        copy_sum += copies[i];
        // copy_sum += copies[i];
        if (copies[i]) fprintf(stderr, "[%zu]: %u\n", i, copies[i]);
    }
    
    fprintf(stderr, "SUM: %zu\n", sum);
    fprintf(stderr, "COPY SUM: %zu\n", copy_sum);
    
    return 0;
}