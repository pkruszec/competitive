#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#include "string_view.h"

#define INSTR_MAX 512
#define INBUF_MAX 256
#define ROADS_MAX 1024
#define POINT_MAX 3

typedef struct {
    char src[POINT_MAX];
    char dst_left[POINT_MAX];
    char dst_right[POINT_MAX];
} Road;

Road *find_road_by_src(Road *roads, size_t road_count, const char *src)
{
    for (size_t i = 0; i < road_count; ++i) {
        if (strncmp(roads[i].src, src, POINT_MAX) == 0) return &roads[i];
    }
    return NULL;
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
    
#if 0
    for (size_t i = 0; i < road_count; ++i) {
        Road *road = &roads[i];
        printf("[%zu] = %.*s -> %.*s, %.*s\n", i, 
               POINT_MAX, road->src,
               POINT_MAX, road->dst_left,
               POINT_MAX, road->dst_right);
    }
#endif
    
    return 0;
}