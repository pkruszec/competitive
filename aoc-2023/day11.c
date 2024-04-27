#include "aoc.h"

#define INBUF_MAX 256
#define SATELLITES_MAX 1024

#define ABS(x) (((x) >= 0) ? (x) : -(x))
#define MIN(a, b) ((a)<(b) ? (a) : (b))
#define MAX(a, b) ((a)>(b) ? (a) : (b))

#define AT(arr, width, x, y) (arr)[(y)*(width) + (x)]

typedef struct Point {
    s64 x;
    s64 y;
} Point;

int main(void)
{
    char board0[INBUF_MAX*INBUF_MAX];
    bool first = true;
    u64 width = 0;
    u64 height = 0;
    
    char inbuf[INBUF_MAX];
    while (fgets(inbuf, INBUF_MAX, stdin)) {
        u64 len = strlen(inbuf);
        if (inbuf[len-1] == '\n') len--;
        
        if (first) {
            width = len;
            first = false;
        }
        
        for (u64 i = 0; i < width; ++i) {
            AT(board0, width, i, height) = inbuf[i];
        }
        
        height++;
    }
    
#if PART2
    //
    
    for (u64 y = 0; y < height; ++y) {
        for (u64 x = 0; x < width; ++x) {
            printf("%c", AT(board0, width, x, y));
        }
        printf("\n");
    }
    
    Point satellites[SATELLITES_MAX];
    u64 satellite_count = 0;
    
    for (u64 y = 0; y < height; ++y) {
        for (u64 x = 0; x < width; ++x) {
            if (AT(board0, width, x, y) == '#') {
                assert(satellite_count < SATELLITES_MAX);
                satellites[satellite_count++] = (Point) {x, y};
            }
        }
    }
    
    u64 count = 1000000;
    
    u64 sum = 0;
    for (u64 i = 0; i < satellite_count-1; ++i) {
        for (u64 j = i+1; j < satellite_count; ++j) {
            Point a = satellites[i];
            Point b = satellites[j];
            
            s64 min_x = MIN(a.x, b.x);
            s64 max_x = MAX(a.x, b.x);
            
            s64 min_y = MIN(a.y, b.y);
            s64 max_y = MAX(a.y, b.y);
            
            u64 dx = 0, dy = 0;
            
            for (s64 i = min_x; i < max_x; ++i) {
                bool is_empty = true;
                for (u64 j = 0; j < height; ++j) {
                    if (AT(board0, width, i, j) == '#') {
                        is_empty = false;
                        break;
                    }
                }
                
                dx += is_empty ? count : 1;
            }
            
            for (s64 i = min_y; i < max_y; ++i) {
                bool is_empty = true;
                for (u64 j = 0; j < width; ++j) {
                    if (AT(board0, width, j, i) == '#') {
                        is_empty = false;
                        break;
                    }
                }
                
                dy += is_empty ? count : 1;
            }
            
            s64 distance = dx + dy;
            sum += distance;
            
            // printf("%llu: {%lld, %lld}, {%lld, %lld}, %lld\n", count, a.x, a.y, b.x, b.y, ABS(a.x-b.x) + ABS(a.y-b.y));
        }
    }
    
    printf("SUM: %llu\n", sum);
    
#else
    // Fill the row-expanded board.
    
    char board1[INBUF_MAX*INBUF_MAX];
    u64 board1_width = width;
    u64 board1_height = 0;
    for (u64 y = 0; y < height; ++y) {
        bool is_clear = true;
        for (u64 x = 0; x < width; ++x) {
            // printf("%c", AT(board0, width, x, y));
            if (AT(board0, width, x, y) != '.') {
                is_clear = false;
                break;
            }
        }
        
        u32 count = (is_clear) ? 2 : 1;
        for (u32 i = 0; i < count; ++i) {
            for (u64 x = 0; x < width; ++x) {
                AT(board1, board1_width, x, board1_height) = AT(board0, width, x, y);
            }
            board1_height++;
        }
        
        // printf(" -> %d\n", is_clear);
    }
    
    // First, determine the final width and height of the column-expanded board.
    
    char board2[INBUF_MAX*INBUF_MAX];
    u64 board2_width = board1_width;
    u64 board2_height = board1_height;
    for (u64 x = 0; x < board1_width; ++x) {
        bool is_clear = true;
        for (u64 y = 0; y < board1_height; ++y) {
            if (AT(board1, board1_width, x, y) != '.') {
                is_clear = false;
                break;
            }
        }
        if (is_clear) board2_width++;
    }
    
    // Fill the column-expanded board.
    
    u64 xp = 0;
    for (u64 x = 0; x < board1_width; ++x) {
        bool is_clear = true;
        for (u64 y = 0; y < board1_height; ++y) {
            if (AT(board1, board1_width, x, y) != '.') {
                is_clear = false;
                break;
            }
        }
        
        u32 count = (is_clear) ? 2 : 1;
        for (u32 i = 0; i < count; ++i) {
            for (u64 y = 0; y < board1_height; ++y) {
                AT(board2, board2_width, xp, y) = AT(board1, board1_width, x, y);
            }
            xp++;
        }
    }
    
    // Debug printing.
    
#if 0
    for (u64 y = 0; y < board1_height; ++y) {
        for (u64 x = 0; x < board1_width; ++x) {
            putc(AT(board1, board1_width, x, y), stdout);
        }
        printf("\n");
    }
    
    printf("%llux%llu\n", board1_width, board1_height);
    
    
    for (u64 y = 0; y < board2_height; ++y) {
        for (u64 x = 0; x < board2_width; ++x) {
            putc(AT(board2, board2_width, x, y), stdout);
        }
        printf("\n");
    }
    
    printf("%llux%llu\n", board2_width, board2_height);
#endif
    
    Point satellites[SATELLITES_MAX];
    u64 satellite_count = 0;
    
    for (u64 y = 0; y < board2_height; ++y) {
        for (u64 x = 0; x < board2_width; ++x) {
            if (AT(board2, board2_width, x, y) == '#') {
                assert(satellite_count < SATELLITES_MAX);
                satellites[satellite_count++] = (Point) {x, y};
            }
        }
    }
    
#if 0
    for (u64 i = 0; i < satellite_count; ++i) {
        printf("[%llu] = {%lld, %lld}\n", i, satellites[i].x, satellites[i].y);
    }
#endif
    
    u64 sum = 0;
    
    assert(satellite_count > 0);
    u64 count = 0;
    for (u64 i = 0; i < satellite_count-1; ++i) {
        for (u64 j = i+1; j < satellite_count; ++j) {
            Point a = satellites[i];
            Point b = satellites[j];
            
            // float dx = fabs(a.x-b.x);
            // float dy = fabs(a.y-b.y);
            
            // u64 distance = (u64)ceil(sqrt(dx*dx + dy*dy));
            s64 distance = ABS(a.x-b.x) + ABS(a.y-b.y);
            
            sum += distance;
            
            // printf("%llu: {%lld, %lld}, {%lld, %lld}, %lld\n", count, a.x, a.y, b.x, b.y, ABS(a.x-b.x) + ABS(a.y-b.y));
            count++;
        }
    }
    printf("count: %llu\n", count);
    printf("SUM: %llu\n", sum);
#endif
    
    return 0;
}