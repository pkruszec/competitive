#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

#define ROWS 256
#define COLS 256

#define array_count(arr) (sizeof(arr) / sizeof((arr)[0]))

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

int main(void)
{
    char board[ROWS][COLS] = {0};
    
    int len = -1;
    size_t row = 0;
    while (fgets(board[row], COLS, stdin)) {
        if (row >= ROWS) {
            fprintf(stderr, "ERROR: Increase the number of rows.\n");
            return 1;
        }
        
        if (len < 0) len = strlen(board[row]);
        if (board[row][len-1] == '\n') board[row][len-1] = '\0';
        
        row++;
    }
    
    size_t sum = 0;
    
    size_t rows_used = row;
    for (size_t i = 0; i < rows_used; ++i) {
        // printf("[%.3zu] = \"%s\"\n", i, board[i]);
        bool is_number_mode = false;
        bool is_next_to_symbol = false;
        
        String_View numsv = {0};
        
        // 507207-600000
        
        for (int j = 0; j < len; ++j) {
            char c = board[i][j];
            is_number_mode = isdigit(c);
            
            if (is_number_mode) {
                if (numsv.vals == NULL) {
                    numsv.vals = &board[i][j];
                }
            }
            
            // ...
            // . 1
            // ...
            //
            // ...
            // 1 8
            // *..
            //
            // ...
            // 1 .
            // ...
            //
            // *..
            // . 8
            // ...
            
            if (is_number_mode) {
                //[i-1][j-1]  [i-1][j]  [i-1][j+1]
                //[i][j-1]    [i][j]    [i][j+1]
                //[i+1][j-1]  [i-1][j]  [i+1][j+1]
                
#if 0
                fprintf(stderr, "i=%d j=%zu\n", i, j);
                fprintf(stderr, "board[100][38] = %c\n", board[100][38]);
#endif
                
#if 0
                char neighbors[] = {
                    (i>0 && j>0) ? board[i-1][j-1]: '\0', 
                    (i>0) ? board[i-1][j] : '\0',
                    (i>0 && j<len) ? board[i-1][j+1] : '\0',
                    (j>0) ? board[i][j-1] : '\0',
                    (j<len) ? board[i][j+1] : '\0',
                    (i<rows_used && j>0) ? board[i+1][j-1] : '\0',
                    (i>0) ? board[i-1][j] : '\0', 
                    (i<rows_used && j<len) ? board[i+1][j+1] : '\0',
                };
#else
                char neighbors[8] = {0};
                if (i>0 && j>0)            neighbors[0] = board[i-1][j-1]; 
                if (i>0)                   neighbors[1] = board[i-1][j];
                if (i>0 && j<len)          neighbors[2] = board[i-1][j+1];
                if (j>0)                   neighbors[3] = board[i][j-1];
                if (j<len)                 neighbors[4] = board[i][j+1];
                if (i<rows_used && j>0)    neighbors[5] = board[i+1][j-1];
                if (i>0)                   neighbors[6] = board[i+1][j]; 
                if (i<rows_used && j<len)  neighbors[7] = board[i+1][j+1];
#endif
                
                // fprintf(stderr, "current = %c\n", board[i][j]);
                
                for (size_t k = 0; k < array_count(neighbors); ++k) {
#if 0
                    if (neighbors[k] == '\0') fprintf(stderr, "H", neighbors[k]);
                    else fprintf(stderr, "%c", neighbors[k]);
                    
                    if (k == 3) fprintf(stderr, "x");
                    if (((k+1) % 3 == 0 || k == 4) && k != 5) fprintf(stderr, "\n");
#endif
                    
                    if (ispunct(neighbors[k]) && neighbors[k] != '.') {
                        is_next_to_symbol = true;
                        //break;
                    }
                }
                // fprintf(stderr, "\n\n");
                
            } else {
                
            }
            
            if (!is_number_mode) {
                if (numsv.count > 0) {
                    if (is_next_to_symbol) {
                        uint32_t num;
                        if (!sv_to_uint32_simple(numsv, 10, &num)) return 1;
                        
                        fprintf(stderr, "NUMBER: %u (%d)\n", num, is_next_to_symbol);
                        
                        sum += num;
                    } else {
                        fprintf(stderr, "%zu:%d NUMBER: %.*s (%d)\n", i+1, j+1, numsv.count, numsv.vals, is_next_to_symbol);
                    }
                }
                
                numsv = (String_View){0};
                is_next_to_symbol = false;
            }
            
            if (is_number_mode) numsv.count++;
            
            //putc(is_number_mode ? (is_next_to_symbol ? 'N' : c) : c, stdout);
        }
        //putc('\n', stdout);
        
    }
    
    fprintf(stderr, "SUM: %zu\n", sum);
}