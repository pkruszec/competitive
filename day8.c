#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

#include "string_view.h"

#define INSTR_MAX 512
#define INBUF_MAX 256
#define ROADS_MAX 1024
#define POINT_MAX 3

#define BUCKET_COUNT 64
#define ROAD_BUCKET_MAX 64

// IN 10 S:
// buckets: 16, per bucket: 256 --- 42000
// buckets: 32, per bucket: 128 --- 65000
// buckets: 64, per bucket: 64  --- 79000
// buckets: 128, per bucket: 32 --- 72000
// buckets: 256, per bucket: 64 --- 75000

// #define BUCKET_COUNT (ROADS_MAX/ROAD_BUCKET_MAX)

#if (BUCKET_COUNT * ROAD_BUCKET_MAX) < ROADS_MAX
#error "hashtable capacity less than array capacity"
#endif

typedef struct {
    char src[POINT_MAX];
    char dst_left[POINT_MAX];
    char dst_right[POINT_MAX];
} Road;

typedef struct {
    Road *vals[ROAD_BUCKET_MAX];
    size_t count;
} Road_Bucket;

uint64_t point_hash(const char *src)
{
    return (src[0] + src[1] + src[2]);
}

bool points_are_equal(const char *a, const char *b)
{
    return (a[0] == b[0] &&
            a[1] == b[1] &&
            a[2] == b[2]
            );
}

Road *find_road_by_src_array(Road *roads, size_t road_count, const char *src)
{
    for (size_t i = 0; i < road_count; ++i) {
        if (points_are_equal(roads[i].src, src)) return &roads[i];
    }
    return NULL;
}

Road *find_road_by_src(Road_Bucket *ht, const char *src)
{
    uint64_t hash = point_hash(src);
    size_t index = hash % BUCKET_COUNT;
    
    Road_Bucket *bucket = &ht[index];
    for (size_t i = 0; i < bucket->count; ++i) {
        if (points_are_equal(bucket->vals[i]->src, src)) return bucket->vals[i];
    }
    
    return NULL;
}

bool all_roads_end_with(Road **nodes, size_t node_count, char suffix)
{
    for (size_t i = 0; i < node_count; ++i) {
        if (nodes[i]->src[POINT_MAX-1] != suffix) return false;
    }
    return true;
}

int main(void)
{
    char instr_buf[INSTR_MAX];
    fgets(instr_buf, INSTR_MAX, stdin);
    String_View instr = sv_lit(instr_buf);
    instr = sv_trim_char_end(instr, '\n');
    
    
    Road roads[ROADS_MAX];
    size_t road_count = 0;
    
    char inbuf[INBUF_MAX];
    while (fgets(inbuf, INBUF_MAX, stdin)) {
        String_View data = sv_lit(inbuf);
        data = sv_trim_char_end(data, '\n');
        if (data.count < 1) continue;
        
        assert(road_count < ROADS_MAX);
        
        String_View src = sv_trim_to_next_char(&data, '=');
        src = sv_trim_char_end(src, ' ');
        
        String_View dst_left = sv_trim_to_next_char(&data, ',');
        dst_left = sv_trim_char_begin(dst_left, ' ');
        dst_left = sv_trim_char_begin(dst_left, '(');
        
        String_View dst_right = data;
        dst_right = sv_trim_char_begin(dst_right, ' ');
        dst_right = sv_trim_char_end(dst_right, ')');
        
        assert(src.count == POINT_MAX);
        assert(dst_left.count == POINT_MAX);
        assert(dst_right.count == POINT_MAX);
        
        Road *road = &roads[road_count];
        strncpy(road->src, src.vals, POINT_MAX);
        strncpy(road->dst_left, dst_left.vals, POINT_MAX);
        strncpy(road->dst_right, dst_right.vals, POINT_MAX);
        road_count++;
        
#if 0
        printf("src = '%.*s', left = '%.*s', right = '%.*s'\n", 
               sv_expand_for_printf(src),
               sv_expand_for_printf(dst_left),
               sv_expand_for_printf(dst_right));
#endif
    }
    
    printf("%.*s\n", sv_expand_for_printf(instr));
    
    // FOR PART 2:
    // We could collect all the nodes ending with A into an array of pointers,
    // and then every tick update all of them in a loop until they all have the Z suffix.
    // We could add another parameter/array of booleans which indicate whether the current node
    // has already been found.
    
#if 0
    size_t count = 0;
    Road *node = find_road_by_src(roads, road_count, "AAA");
    assert(node);
    do {
        for (size_t i = 0; i < instr.count; ++i) {
            char step = instr.vals[i];
            if (step == 'R') {
                node = find_road_by_src(roads, road_count, node->dst_right);
            } else if (step == 'L') {
                node = find_road_by_src(roads, road_count, node->dst_left);
            } else {
                assert(false && "step is neither R nor L");
            }
            
            ++count;
            if (strncmp(node->src, "ZZZ", POINT_MAX) == 0) break;
            
        }
    } while (strncmp(node->src, "ZZZ", POINT_MAX) != 0);
    printf("COUNT: %zu\n", count);
#endif
    
    Road_Bucket road_ht[BUCKET_COUNT] = {0};
    for (size_t i = 0; i < road_count; ++i) {
        uint64_t hash = point_hash(roads[i].src);
        size_t index = hash % BUCKET_COUNT;
        Road_Bucket *bucket = &road_ht[index];
        assert(bucket->count < ROAD_BUCKET_MAX);
        bucket->vals[bucket->count++] = &roads[i];
    }
    
#if 0
    for (size_t i = 0; i < BUCKET_COUNT; ++i) {
        printf("BUCKET %zu: %zu\n", i, road_ht[i].count);
    }
#endif
    
    Road *nodes[ROADS_MAX];
    size_t node_count = 0;
    for (size_t i = 0; i < road_count; ++i) {
        if (roads[i].src[POINT_MAX-1] == 'A') {
            assert(node_count < ROADS_MAX);
            nodes[node_count++] = &roads[i];
        }
    }
    
    // 6385640000 -> too low
    // 9486644028399441209 -> not right
    
#if 1
    size_t counts[ROADS_MAX];
    
    // size_t product = 1;
    for (size_t i = 0; i < node_count; ++i) {
        size_t count = 0;
        
        while (true) {
            for (size_t j = 0; j < instr.count; ++j) {
                char step = instr.vals[j];
                
                const char *dst;
                if (step == 'R') {
                    dst = nodes[i]->dst_right;
                } else if (step == 'L') {
                    dst = nodes[i]->dst_left;
                } else {
                    assert(false && "step is neither R nor L");
                }
                
                nodes[i] = find_road_by_src_array(roads, road_count, dst);
                ++count;
                
                if (nodes[i]->src[POINT_MAX - 1] == 'Z') goto after;
            }
        }
        after:
        
        counts[i] = count;
        
        // printf("product: %zu * %zu = \n", product, count);
        // product *= count;
    }
    
    for (size_t i = 0; i < node_count; ++i) {
        printf("[%zu] = %zu\n", i, counts[i]);
    }
    
    // printf("PRODUCT: %zu\n", product);
    
#else
    
    size_t iter = 0;
    size_t count = 0;
    while (!all_roads_end_with(nodes, node_count, 'Z')) {
        if (iter % 10000 == 0) {
            printf("%d -> %zu (count=%zu)\n", time(0), iter, count);
            for (size_t i = 0; i < node_count; ++i) {
                printf("- %zu: %.*s\n", i, POINT_MAX, nodes[i]->src);
            }
        }
        
        for (size_t i = 0; i < instr.count; ++i) {
            
            char step = instr.vals[i];
            
#if 0
            intptr_t off;
            if (step == 'R') {
                off = offsetof(Road, dst_right);
            } else if (step == 'L') {
                off = offsetof(Road, dst_left);
            } else {
                assert(false && "step is neither R nor L");
            }
#elif 0
            intptr_t off = step == 'R' ? offsetof(Road, dst_right) : offsetof(Road, dst_left);
#else
            const intptr_t off = (step == 'R') * offsetof(Road, dst_right) + (step == 'L') * offsetof(Road, dst_left);
#endif
            
            
            ++count;
            for (size_t j = 0; j < node_count; ++j) {
                Road *node = nodes[j];
                //if (node->src[POINT_MAX-1] == 'Z') continue;
                
                const char *dst = (intptr_t)(node) + off;
                
#if 0
                const char *dst;
                if (step == 'R') {
                    dst = node->dst_right;
                } else if (step == 'L') {
                    dst = node->dst_left;
                } else {
                    assert(false && "step is neither R nor L");
                }
#endif
                
                // nodes[j] = find_road_by_src(roads, road_count, dst);
                nodes[j] = find_road_by_src(road_ht, dst);
            }
            
            if (all_roads_end_with(nodes, node_count, 'Z')) goto after;
        }
        ++iter;
    }
    after:
    
    // 20777  - too low
    // 100467 - too low
    
    // 5 -> 10 s -- strncmp -> points_are_equal
    // 5 -> 10 s -- ifs -> offset
    // 5 -> 10 s -- no checking other than while
    // 10 -> 25 s -- only check for R
    // 10 -> 25 s -- branchless
    
    for (size_t i = 0; i < node_count; ++i) {
        printf("%.*s\n", POINT_MAX, nodes[i]->src);
    }
    
    printf("COUNT: %zu\n", count);
    
#if 0
    for (size_t i = 0; i < road_count; ++i) {
        Road *road = &roads[i];
        printf("[%zu] = %.*s -> %.*s, %.*s\n", i, 
               POINT_MAX, road->src,
               POINT_MAX, road->dst_left,
               POINT_MAX, road->dst_right);
    }
#endif
#endif
    
    return 0;
}