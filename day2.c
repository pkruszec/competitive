// = Advent of Code 2023 - day 2
// :author: Paweł Kruszec
// :email: pakruszec@gmail.com
// :revdate: 2023-12-02

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdint.h>

#define array_count(arr) (sizeof(arr) / sizeof((arr)[0]))
#define char_array_count(arr) (array_count(arr) - sizeof(char))

typedef struct {
    const char *vals;
    size_t count;
} String_View;

#define sv_lit(cstr) (String_View){.vals = (cstr), .count = strlen(cstr)}

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

bool extract_count_and_color(String_View data_sv, size_t *count, String_View *color_sv)
{
    if (count == NULL || color_sv == NULL) return false;
    
    String_View part = {0};
    for (size_t i = 0; i < 2; ++i) {
        if (part.vals >= sv_end(data_sv)) return false;
        part = sv_trim_to_next_char(&data_sv, ' ');
        
        switch (i) {
            case 0: {
                if (!sv_to_uint32_simple(part, 10, count)) return false;
            }break;
            case 1: {
                *color_sv = part;
            }break;
            default: break;
        }
    }
    
    return true;
}

int main(void)
{
    char prefix[] = "Game ";
    
    String_View red = sv_lit("red");
    String_View green = sv_lit("green");
    String_View blue = sv_lit("blue");
    
    size_t limit_red = 12;
    size_t limit_green = 13;
    size_t limit_blue = 14;
    
    size_t sum = 0;
    size_t power_sum = 0;
    
    char line[1024];
    while (fgets(line, array_count(line), stdin)) {
        
        size_t line_len = strlen(line);
        if (line_len == 0) continue;
        
        // chop newline
        if (line[line_len-1] == '\n') {
            line[line_len-1] = '\0';
            line_len--;
        }
        
        if (line_len <= char_array_count(prefix)) continue;
        
        line_len -= char_array_count(prefix);
        char *working_line = line + char_array_count(prefix);
        
        String_View linesv = {
            .vals = working_line,
            .count = line_len
        };
        
        String_View idsv = {
            .vals = working_line,
            .count = 0
        };
        
        for (size_t i = 0; i < linesv.count; ++i, ++idsv.count) {
            if (idsv.vals[i] == ':') break;
        }
        
        uint32_t id;
        if (!sv_to_uint32_simple(idsv, 10, &id)) return 1;
        
        
        size_t offset = idsv.count + 1;
        String_View line_without_idsv = {
            .vals = linesv.vals + offset,
            .count = linesv.count - offset
        };
        
        size_t max_red = 0;
        size_t max_green = 0;
        size_t max_blue = 0;
        
        String_View worksv = line_without_idsv;
        String_View subsv = {0};
        while (subsv.vals < sv_end(worksv)) {
            subsv = sv_trim_to_next_char(&worksv, ';');
            subsv = sv_trim_char_begin(subsv, ' ');
            
            size_t count_red = 0, count_green = 0, count_blue = 0;
            
            String_View count_and_color_sv = {0};
            while (count_and_color_sv.vals < sv_end(subsv)) {
                count_and_color_sv = sv_trim_to_next_char(&subsv, ',');
                count_and_color_sv = sv_trim_char_begin(count_and_color_sv, ' ');
                if (count_and_color_sv.count == 0) break;
                
                
                size_t count;
                String_View color_sv;
                if (!extract_count_and_color(count_and_color_sv, &count, &color_sv)) return 1;
                
                if (sv_equal(color_sv, red)) {
                    count_red += count;
                } else if (sv_equal(color_sv, green)) {
                    count_green += count;
                } else if (sv_equal(color_sv, blue)) {
                    count_blue += count;
                }
                
            }
            
            if (count_red > max_red) max_red = count_red;
            if (count_green > max_green) max_green = count_green;
            if (count_blue > max_blue) max_blue = count_blue;
            
        }
        
        if (max_red <= limit_red && 
            max_green <= limit_green &&
            max_blue <= limit_blue) {
            
            sum += id;
        }
        
        power_sum += max_red*max_green*max_blue;
    }
    
    printf("sum: %zu\n", sum);
    printf("power_sum: %zu\n", power_sum);
    
    return 0;
}