// = Advent of Code 2023 - day 1
// :author: Paweł Kruszec
// :email: pakruszec@gmail.com
// :revdate: 2023-12-01
//
// This program calculates both part 1 and 2 solutions.

#include <stdio.h>
#include <ctype.h>

#define array_count(arr) (sizeof(arr)/sizeof((arr)[0]))

int digit_offset = 1;
char *digits[] = {
    "one", 
    "two", 
    "three", 
    "four", 
    "five", 
    "six", 
    "seven", 
    "eight",
    "nine",
};

int check_word_digit(char *line, size_t line_count, size_t i)
{
    char *sub = line+i;
    size_t sub_count = line_count-i;
    
    for (size_t i = 0; i < array_count(digits); ++i) {
        size_t digit_len = strlen(digits[i]);
        if (sub_count < digit_len) continue;
        if (strncmp(sub, digits[i], digit_len) != 0) continue;
        
        return digit_offset + i;
    }
    
    return -1;
}

int main(void)
{
    size_t sum = 0;
    
    // enough for this puzzle
    char line[256];
    
    while (fgets(line, sizeof(line), stdin)) {
        size_t line_count = strlen(line);
        line[line_count-1] = '\0';
        
        int first_digit = 0;
        int last_digit = 0;
        
        // finding first digit
        for (size_t i = 0; i < line_count; ++i) {
            if (isdigit(line[i])) {
                first_digit = line[i] - '0';
                break;
            } else {
                int digit = check_word_digit(line, line_count, i);
                if (digit >= 0) {
                    first_digit = digit;
                    break;
                }
                else continue;
            }
        }
        
        // finding last digit
        for (size_t i = 0; i < line_count; ++i) {
            size_t rev_i = line_count - i - 1;
            if (isdigit(line[rev_i])) {
                last_digit = line[rev_i] - '0';
                break;
            } else {
                int digit = check_word_digit(line, line_count, rev_i);
                if (digit >= 0) {
                    last_digit = digit;
                    break;
                }
                else continue;
            }
            
        }
        
        int num = 10*first_digit + last_digit;
        
        sum += num;
    }
    
    printf("sum: %zu\n", sum);
}