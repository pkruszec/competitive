#include "aoc.h"

#define INBUF_MAX 256
#define NEIGHBOR_COUNT 8

typedef enum Block_Type {
    BLOCK_UNKNOWN = 0,
    BLOCK_GROUND,
    BLOCK_HORIZ,
    BLOCK_VERT,
    BLOCK_90_NE,
    BLOCK_90_NW,
    BLOCK_90_SW,
    BLOCK_90_SE,
    BLOCK_START,
} Block_Type;

typedef struct Block_Pair {
    Block_Type fst, snd;
} Block_Pair;

typedef struct Point {
    s64 x, y;
} Point;

typedef struct Point_Pair {
    Point fst, snd;
} Point_Pair;

typedef struct Blocks {
    Block_Type *items;
    u64 width;
    u64 height;
} Blocks;

#define block_at(blocks, x, y) (blocks)->items[((y)*(blocks)->width)+(x)]

inline bool point_equal(Point a, Point b)
{
    return (a.x==b.x) && (a.y==b.y);
}

Block_Type block_type_from_char(char c)
{
    switch (c) {
        case '.': return BLOCK_GROUND; break;
        case '-': return BLOCK_HORIZ; break;
        case '|': return BLOCK_VERT; break;
        case 'L': return BLOCK_90_NE; break;
        case 'J': return BLOCK_90_NW; break;
        case '7': return BLOCK_90_SW; break;
        case 'F': return BLOCK_90_SE; break;
        case 'S': return BLOCK_START; break;
        default: break;
    }
    return BLOCK_UNKNOWN;
}

const char *block_type_repr(Block_Type type)
{
    switch (type) {
        case BLOCK_GROUND: return "GROUND"; break;
        case BLOCK_HORIZ:  return "HORIZ"; break;
        case BLOCK_VERT:   return "VERT"; break;
        case BLOCK_90_NE:  return "90_NE"; break;
        case BLOCK_90_NW:  return "90_NW"; break;
        case BLOCK_90_SW:  return "90_SW"; break;
        case BLOCK_90_SE:  return "90_SE"; break;
        case BLOCK_START:  return "START"; break;
        default: break;
    }
    return "UNKNOWN";
}

inline bool block_is_pipe(Block_Type type)
{
    return (
            type != BLOCK_UNKNOWN &&
            type != BLOCK_GROUND &&
            type != BLOCK_START
            );
}

// 012
// 3 4
// 567
//
// [x-1,y-1] [x,y-1] [x+1,y-1]
// [x-1,y]   [x,y]   [x+1,y]
// [x-1,y+1] [x,y+1] [x+1,y+1]
void get_neighboring_blocks(Blocks *blocks, Block_Type neighbors[NEIGHBOR_COUNT], s64 x, s64 y)
{
    u64 w = blocks->width;
    u64 h = blocks->height;
    
    neighbors[0] = (x>0 && y>0) ? (block_at(blocks, x-1, y-1)) : (BLOCK_UNKNOWN);
    neighbors[1] = (y>0)        ? (block_at(blocks, x,   y-1)) : (BLOCK_UNKNOWN);
    neighbors[2] = (x<w && y>0) ? (block_at(blocks, x+1, y-1)) : (BLOCK_UNKNOWN);
    neighbors[3] = (x>0)        ? (block_at(blocks, x-1, y))   : (BLOCK_UNKNOWN);
    neighbors[4] = (x<w)        ? (block_at(blocks, x+1, y))   : (BLOCK_UNKNOWN);
    neighbors[5] = (x>0 && y<h) ? (block_at(blocks, x-1, y+1)) : (BLOCK_UNKNOWN);
    neighbors[6] = (y<h)        ? (block_at(blocks, x,   y+1)) : (BLOCK_UNKNOWN);
    neighbors[7] = (x<w && y<h) ? (block_at(blocks, x+1, y+1)) : (BLOCK_UNKNOWN);
}

Point get_neighbor_offset(u32 i)
{
    switch (i) {
        case 0: return (Point) {-1, -1}; break;
        case 1: return (Point) {0, -1}; break;
        case 2: return (Point) {+1, -1}; break;
        case 3: return (Point) {-1, 0}; break;
        case 4: return (Point) {+1, 0}; break;
        case 5: return (Point) {-1, +1}; break;
        case 6: return (Point) {0, +1}; break;
        case 7: return (Point) {+1, +1}; break;
    }
    return (Point) {0};
}

#if 0
Point_Pair get_connecting_pipes(Blocks *blocks, s64 x, s64 y)
{
    Block_Type neighbors[NEIGHBOR_COUNT] = {0};
    get_neighboring_blocks(blocks, neighbors, x, y);
    
    Point_Pair pair = {0};
    
    u8 found = 0;
    for (u32 i = 0; i < NEIGHBOR_COUNT; ++i) {
        // Dumb way to ensure that we're not checking diagonals.
        if (i != 1 && i != 3 && i != 4 && i != 6) continue;
        
        if (block_is_pipe(neighbors[i]) && found < 2) {
            found++;
            Point off = get_neighbor_offset(i);
            if (found == 1) {
                pair.fst = (Point) {x+off.x, y+off.y};
            } else if (found == 2) {
                pair.snd = (Point) {x+off.x, y+off.y};
            }
        }
    }
    
    return pair;
}
#else
Point_Pair get_connecting_pipes(Blocks *blocks, s64 x, s64 y, u8 *count)
{
    Block_Type neighbors[NEIGHBOR_COUNT] = {0};
    get_neighboring_blocks(blocks, neighbors, x, y);
    
    Point_Pair pair = {0};
    Point *points = (Point *)(&pair);
    
    // points[0] = (Point){x, y};
    // points[1] = (Point){x, y};
    
    u8 found = 0;
    
    //  1
    // 3x4
    //  6
    
    Block_Type current = block_at(blocks, x, y);
    
    Point off;
    
    printf("current: %s\n", block_type_repr(block_at(blocks, x, y)));
    off = get_neighbor_offset(1);
    printf("%llu: %s\n", 1, block_type_repr(block_at(blocks, x+off.x, y+off.y)));
    off = get_neighbor_offset(3);
    printf("%llu: %s\n", 3, block_type_repr(block_at(blocks, x+off.x, y+off.y)));
    off = get_neighbor_offset(4);
    printf("%llu: %s\n", 4, block_type_repr(block_at(blocks, x+off.x, y+off.y)));
    off = get_neighbor_offset(6);
    printf("%llu: %s\n", 6, block_type_repr(block_at(blocks, x+off.x, y+off.y)));
    
    
    if (neighbors[1] == BLOCK_VERT ||
        neighbors[1] == BLOCK_90_SW ||
        neighbors[1] == BLOCK_90_SE) {
        
        assert(found < 2);
        Point off = get_neighbor_offset(1);
        points[found++] = (Point) {x+off.x, y+off.y};
    }
    
    if ((current != BLOCK_VERT && neighbors[3] == BLOCK_HORIZ) ||
        ((current == BLOCK_HORIZ || current == BLOCK_90_NE || current == BLOCK_90_SE) && (neighbors[3] == BLOCK_90_NE || neighbors[3] == BLOCK_90_SE))) {
        
        assert(found < 2);
        Point off = get_neighbor_offset(3);
        points[found++] = (Point) {x+off.x, y+off.y};
    }
    
    if ((current != BLOCK_VERT && neighbors[4] == BLOCK_HORIZ) ||
        ((current == BLOCK_HORIZ || current == BLOCK_90_NW || current == BLOCK_90_SW) && (neighbors[4] == BLOCK_90_NW || neighbors[4] == BLOCK_90_SW))) {
        
        assert(found < 2);
        Point off = get_neighbor_offset(4);
        points[found++] = (Point) {x+off.x, y+off.y};
    }
    
    if (neighbors[6] == BLOCK_VERT ||
        neighbors[6] == BLOCK_90_NW ||
        neighbors[6] == BLOCK_90_NE) {
        
        assert(found < 2);
        Point off = get_neighbor_offset(6);
        points[found++] = (Point) {x+off.x, y+off.y};
    }
    
    if (count) *count = found;
    
    return pair;
}
#endif

// Write a function that returns if a particular block type is allowed to connect to another block type from a particular side.

int main(void)
{
    char board[INBUF_MAX][INBUF_MAX];
    
    u64 width = 0;
    u64 height = 0;
    
    while (fgets(board[height], INBUF_MAX, stdin)) {
        // Quick newline trimming without string view.
        if (!width) width = strlen(board[height]) - 1;
        height++;
    }
    
    printf("%llux%llu\n", width, height);
    
    s64 sx = -1;
    s64 sy = -1;
    bool found = false;
    
    Block_Type block_array[INBUF_MAX*INBUF_MAX];
    Blocks blocks = {
        .items = block_array,
        .width = width,
        .height = height
    };
    
    for (u64 i = 0; i < height; ++i) {
        for (u64 j = 0; j < width; ++j) {
            printf("%c", board[i][j]);
            
            Block_Type block = block_type_from_char(board[i][j]);
            block_at(&blocks, j, i) = block;
            
            if (!found && block == BLOCK_START) {
                sx = j;
                sy = i;
                found = true;
            }
        }
        
        printf("\n");
    }
    
    assert(sx >= 0 && sy >= 0);
    
    Block_Type neighbors[NEIGHBOR_COUNT] = {0};
    get_neighboring_blocks(&blocks, neighbors, sx, sy);
    
#if 0
    for (u32 i = 0; i < NEIGHBOR_COUNT; ++i) {
        printf("[%u] = %s\n", i, block_type_repr(neighbors[i]));
    }
#endif
    
    Point_Pair pair = get_connecting_pipes(&blocks, sx, sy, NULL);
    
    Point fst = pair.fst;
    Point snd = pair.snd;
    
    Point fst_last = {sx, sy};
    Point snd_last = {sx, sy};
    
    u64 fst_count = 0;
    u64 snd_count = 0;
    
    while (!point_equal(fst, snd)) {
        u8 tmp_fst_count = 0;
        u8 tmp_snd_count = 0;
        
        printf("fst_last: (%lld, %lld) snd_last: (%lld, %lld)\n", fst_last.x, fst_last.y, snd_last.x, snd_last.y);
        printf("fst: (%lld, %lld) snd: (%lld, %lld)\n", fst.x, fst.y, snd.x, snd.y);
        
        Point fst_new, snd_new;
        
        Point_Pair fst_new_pair = get_connecting_pipes(&blocks, fst.x, fst.y, &tmp_fst_count);
        if (tmp_fst_count == 2) 
            fst_new = (point_equal(fst_new_pair.fst, fst_last) ? (fst_new_pair.snd) : (fst_new_pair.fst));
        else
            fst_new = fst_new_pair.fst;
        ++fst_count;
        
        Point_Pair snd_new_pair = get_connecting_pipes(&blocks, snd.x, snd.y, &tmp_snd_count);
        if (tmp_snd_count == 2)
            snd_new = (point_equal(snd_new_pair.fst, snd_last) ? (snd_new_pair.snd) : (snd_new_pair.fst));
        else
            snd_new = snd_new_pair.fst;
        ++snd_count;
        
        printf("fst_new: (%lld, %lld)/(%lld, %lld) snd_new: (%lld, %lld)/(%lld, %lld)\n\n", 
               fst_new_pair.fst.x, fst_new_pair.fst.y,
               fst_new_pair.snd.x, fst_new_pair.snd.y,
               snd_new_pair.fst.x, snd_new_pair.fst.y,
               snd_new_pair.snd.x, snd_new_pair.snd.y
               );
        
        fst_last = fst;
        snd_last = snd;
        
        fst = fst_new;
        snd = snd_new;
        
        // if (fst_count > 10) break;
    }
    
    fst_count++;
    snd_count++;
    
    printf("fst: %llu snd: %llu\n", fst_count, snd_count);
    
#if 0
    printf("(%s, %s)\n", 
           block_type_repr(block_at(&blocks, fst.x, fst.y)), 
           block_type_repr(block_at(&blocks, snd.x, snd.y)));
#endif
    
    return 0;
}