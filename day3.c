// = Advent of Code 2023 - day 3
// :author: Paweł Kruszec
// :email: pakruszec@gmail.com
// :revdate: 2023-12-03

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

typedef struct {
    bool valid;
    int a;
    int b;
} Gear;

typedef struct {
    bool valid;
    int i;
    int j;
} Neighbor;

#define NEIGHBOR_COUNT 8
void get_neighbors(Neighbor neighbors[NEIGHBOR_COUNT], int i, int j, size_t rows_used, size_t len)
{
    memset(neighbors, 0, sizeof(neighbors[0])*NEIGHBOR_COUNT);
    if (i>0 && j>0)            neighbors[0] = (Neighbor) {true, i-1, j-1}; 
    if (i>0)                   neighbors[1] = (Neighbor) {true, i-1, j};
    if (i>0 && j<len)          neighbors[2] = (Neighbor) {true, i-1, j+1};
    if (j>0)                   neighbors[3] = (Neighbor) {true, i, j-1};
    if (j<len)                 neighbors[4] = (Neighbor) {true, i, j+1};
    if (i<rows_used && j>0)    neighbors[5] = (Neighbor) {true, i+1, j-1};
    if (i<rows_used)           neighbors[6] = (Neighbor) {true, i+1, j}; 
    if (i<rows_used && j<len)  neighbors[7] = (Neighbor) {true, i+1, j+1};
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
    
    Gear gears[ROWS][COLS] = {0};
    
    size_t sum = 0;
    size_t gear_ratio_sum = 0;
    
    size_t rows_used = row;
    for (size_t i = 0; i < rows_used; ++i) {
        bool is_number_mode = false;
        bool is_next_to_symbol = false;
        
        String_View numsv = {0};
        
        for (int j = 0; j < len; ++j) {
            char c = board[i][j];
            is_number_mode = isdigit(c);
            
            if (is_number_mode) {
                if (numsv.vals == NULL) {
                    numsv.vals = &board[i][j];
                }
            }
            
            if (is_number_mode) {
                //[i-1][j-1]  [i-1][j]  [i-1][j+1]
                //[i][j-1]    [i][j]    [i][j+1]
                //[i+1][j-1]  [i-1][j]  [i+1][j+1]
                
                Neighbor neighbors[8];
                get_neighbors(neighbors, i, j, rows_used, len);
                
                for (size_t k = 0; k < array_count(neighbors); ++k) {
                    if (!neighbors[k].valid) continue;
                    char value = board[neighbors[k].i][neighbors[k].j];
#if 0
                    if (value == '\0') fprintf(stderr, "H", value);
                    else fprintf(stderr, "%c", value);
                    
                    if (k == 3) fprintf(stderr, "x");
                    if (((k+1) % 3 == 0 || k == 4) && k != 5) fprintf(stderr, "\n");
#endif
                    
                    if (ispunct(value) && value != '.') {
                        if (value == '*') {
                            // fprintf(stderr, "* at i=%zu, j=%d\n", neighbors[k].i, neighbors[k].j);
                            gears[neighbors[k].i][neighbors[k].j].valid = true;
                        }
                        
                        is_next_to_symbol = true;
                        // break;
                    }
                }
            }
            
            if (!is_number_mode) {
                if (numsv.count > 0) {
                    if (is_next_to_symbol) {
                        uint32_t num;
                        if (!sv_to_uint32_simple(numsv, 10, &num)) return 1;
                        
                        size_t index = i*len + (size_t) (numsv.vals - board[i]);
                        fprintf(stderr, "index: %zu count: %zu\n", index, numsv.count);
                        // get x and y from index
                        
                        Neighbor neighbors[NEIGHBOR_COUNT];
                        
                        for (size_t k = 0; k < numsv.count; ++k) {
                            size_t y = (index+k) / len;
                            size_t x = (index+k) % len;
                            fprintf(stderr, "[%zu] = %c\n", k, board[y][x]);
                            get_neighbors(neighbors, y, x, rows_used, len);
                            
                            for (size_t k = 0; k < array_count(neighbors); ++k) {
                                char value = board[neighbors[k].i][neighbors[k].j];
                                
#if 0
                                if (neighbors[k].valid) fprintf(stderr, "%c", value);
                                else fprintf(stderr, "H", value);
                                
                                if (k == 3) fprintf(stderr, "x");
                                if (((k+1) % 3 == 0 || k == 4) && k != 5) fprintf(stderr, "\n");
#endif
                                Gear *gear = &gears[neighbors[k].i][neighbors[k].j];
                                if (value == '*' && gear->valid) {
                                    fprintf(stderr, "neighboring gear!\n");
                                    if (gear->a == 0) {
                                        gear->a = num;
                                        // gear->b = 0;
                                    } else if (gear->b == 0) {
                                        gear->b = num;
                                    } else {
                                        gear->valid = false;
                                    }
                                    goto after_loop;
                                    // 29659895
                                }
                            }
                            // fprintf(stderr, "\n\n");
                        }
                        after_loop:
                        
                        // Neighbor neighbors[8];
                        // get_neighbors(neighbors, i, j, rows_used, len);
                        
                        fprintf(stderr, "NUMBER: %u (%d)\n", num, is_next_to_symbol);
                        
                        sum += num;
                    } else {
                        // fprintf(stderr, "%zu:%d NUMBER: %.*s (%d)\n", i+1, j+1, numsv.count, numsv.vals, is_next_to_symbol);
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
    
    for (size_t i = 0; i < rows_used; ++i) {
        for (size_t j = 0; j < len; ++j) {
            Gear *gear = &gears[i][j];
            if (!gear->valid) continue;
            if (gear->b == 0) continue;
            
            fprintf(stderr, "VALID GEAR: i=%zu j=%zu a=%d b=%d\n", i, j, gear->a, gear->b);
            
            gear_ratio_sum += gear->a * gear->b;
        }
    }
    
#if 0
    for (size_t i = 0; i < rows_used; ++i) {
        for (size_t j = 0; j < len; ++j) {
            char c = board[i][j];
            if (c != '*') continue;
            
            fprintf(stderr, "i=%zu j=%d\n", i, j);
            
            // This one with the actual cell.
            char neighbors[9] = {0};
            if (i>0 && j>0)            neighbors[0] = board[i-1][j-1]; 
            if (i>0)                   neighbors[1] = board[i-1][j];
            if (i>0 && j<len)          neighbors[2] = board[i-1][j+1];
            if (j>0)                   neighbors[3] = board[i][j-1];
            neighbors[4] = board[i][j];
            if (j<len)                 neighbors[5] = board[i][j+1];
            if (i<rows_used && j>0)    neighbors[6] = board[i+1][j-1];
            if (i>0)                   neighbors[7] = board[i+1][j]; 
            if (i<rows_used && j<len)  neighbors[8] = board[i+1][j+1];
            
            for (size_t k = 0; k < array_count(neighbors); ++k) {
                
                if (neighbors[k] == '\0') fprintf(stderr, "H", neighbors[k]);
                else fprintf(stderr, "%c", neighbors[k]);
                
                if (((k+1) % 3 == 0)) fprintf(stderr, "\n");
            }
            
            size_t count = 0;
            
            for (size_t k = 0; k < 3; ++k) {
                bool is_num = false;
                for (size_t l = 0; l < 3; ++l) {
                    char c = neighbors[k*3 + l];
                    bool c_is_digit = isdigit(c);
                    
                    if (c_is_digit && !is_num) {
                        count++;
                        is_num = true;
                    }
                    
                    if (!c_is_digit && is_num) {
                        is_num = false;
                    }
                }
            }
            
            if (count == 2) gear_ratio_sum = 
                
                fprintf(stderr, "count = %zu\n", count);
            fprintf(stderr, "\n\n");
        }
    }
#endif
    
    fprintf(stderr, "SUM: %zu\n", sum);
    fprintf(stderr, "GEAR RATIO SUM: %zu\n", gear_ratio_sum);
}