#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "string_view.h"

typedef int64_t s64;

#define LINE_MAX 1024
#define NUMBERS_MAX 256
#define NUMBER_ARRAYS_MAX 256

bool all_s64(s64 *array, size_t count, s64 value)
{
    for (size_t i = 0; i < count; ++i) {
        if (array[i] != value) return false;
    }
    return true;
}

int main(void)
{
    char line_buf[LINE_MAX];
    s64 numbers[NUMBER_ARRAYS_MAX][NUMBERS_MAX] = {0};
    size_t number_counts[NUMBER_ARRAYS_MAX] = {0};
    
    size_t sum = 0;
    s64 back_sum = 0;
    
    size_t number_array_count = 0;
    while (fgets(line_buf, LINE_MAX, stdin)) {
        String_View line = sv_lit(line_buf);
        line = sv_trim_char_end(line, '\n');
        printf("%.*s\n", sv_expand_for_printf(line));
        
        number_array_count = 0;
        
        number_counts[0] = 0;
        String_View num_sv = {0};
        while (num_sv.vals < sv_end(line)) {
            num_sv = sv_trim_to_next_char(&line, ' ');
            if (num_sv.count < 1) continue;
            assert(number_counts[0] < NUMBERS_MAX);
            assert(sv_to_int64_simple(num_sv, 10, &(numbers[0][number_counts[0]++])));
        }
        number_array_count++;
        
        while (!all_s64(numbers[number_array_count-1], number_counts[number_array_count-1], 0)) {
            number_counts[number_array_count] = 0;
            s64 *array = numbers[number_array_count];
            
            assert(number_array_count > 0);
            
            s64 *prev = numbers[number_array_count-1];
            size_t prev_count = number_counts[number_array_count-1];
            
            assert(prev_count > 0);
            
            for (size_t i = 1; i < prev_count; ++i) {
                s64 diff = prev[i] - prev[i-1];
                array[number_counts[number_array_count]++] = diff;
            }
            
            number_array_count++;
        }
        
        printf("%zu -> %zu\n", number_array_count, number_counts[number_array_count-1]);
        
        for (size_t j = 0; j < number_array_count; ++j) {
            printf("ARRAY %zu:\n", j);
            for (size_t i = 0; i < number_counts[j]; ++i) {
                printf("   [%zu] = %lld\n", i, numbers[j][i]);
            }
        }
        
        assert(number_array_count > 1);
        s64 *first = numbers[0];
        size_t first_count = number_counts[0];
        
        s64 extrapolated = first[first_count-1];
        
        for (size_t i = 1; i < number_array_count; ++i) {
            s64 *current = numbers[i];
            size_t current_count = number_counts[i];
            assert(current_count >= 1);
            
            extrapolated += current[current_count-1];
        }
        
        sum += extrapolated;
        
        assert(number_array_count > 2);
        
        
        
        
        
        // s64 extrapolated_back = numbers[number_array_count-2][0];
        // s64 extrapolated_back = 0;
        s64 extrapolated_back = numbers[number_array_count-1][0];
        for (size_t ri = 1; ri < number_array_count; ++ri) {
            size_t i = number_array_count-ri-1;
            
            // extrapolated_back += (numbers[i-1][0] - numbers[i][0]);
            // extrapolated_back -= (numbers[i][0]);
            // extrapolated_back += (numbers[i][0] - numbers[i+1][0]);
            
            extrapolated_back = numbers[i][0] - extrapolated_back;
            
            printf("%zu, prev: %lld current: %lld ex: %lld\n", 
                   i, 
                   numbers[i+1][0], numbers[i][0], 
                   extrapolated_back);
        }
        
#if 0
        s64 extrapolated_back = first[0];
        for (size_t i = 1; i < number_array_count; ++i) {
            s64 *current = numbers[i];
            size_t current_count = number_counts[i];
            assert(current_count > 0);
            extrapolated_back -= current[0];
        }
#endif
        
        back_sum += extrapolated_back;
        
        // 0   1   3   6   10   15   21
        //   1   2   3   4    5    6
        //     1   1   1   1    1
        //       0   0   0   0
        
        // 18446744073709536023 - too high
        
        
        printf("extrapolated back: %lld\n", extrapolated_back);
    }
    
    printf("SUM: %zu\n", sum);
    printf("BACK SUM: %lld\n", back_sum);
    
    return 0;
}