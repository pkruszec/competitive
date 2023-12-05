#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

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

bool sv_to_uint64_simple(String_View sv, unsigned int base, uint64_t *out_num)
{
    if (out_num == NULL) return false;
    if (sv.count < 1) return false;
    if (base > 10) return false;
    uint64_t num = 0;
    uint64_t mul = 1;
    
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
// while (line.vals < sv_end(copy)) {
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

String_View sv_trim_char_end(String_View data, char c)
{
    String_View new_data = data;
    
    for (size_t i = 0; i < data.count; ++i) {
        if (data.vals[data.count-i-1] == c) {
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

#define IN_BUF_MAX 1024
#define SEEDS_MAX 256
#define RANGES_MAX 64
#define MAPS_MAX 128
#define MAP_BUF_MAX 32

typedef struct {
    uint64_t dst;
    uint64_t src;
    uint64_t count;
} Range;

typedef struct {
    char from_buf[MAP_BUF_MAX];
    char to_buf[MAP_BUF_MAX];
    String_View from;
    String_View to;
    Range ranges[RANGES_MAX];
    size_t range_count;
} Map;

typedef struct {
    uint64_t id;
    uint64_t value;
} Seed;

Map *find_map_by_from(Map *maps, size_t map_count, String_View from)
{
    for (size_t i = 0; i < map_count; ++i) {
        if (sv_equal(maps[i].from, from)) return &maps[i];
    }
    
    return NULL;
}

uint64_t map_seed_value(Map *map, uint64_t value)
{
    Range *valid = NULL;
    for (size_t j = 0; j < map->range_count; ++j) {
        Range *range = &map->ranges[j];
        if (value >= range->src && value < (range->src + range->count)) {
            valid = range;
            break;
        }
    }
    
    if (valid) {
        uint64_t result = valid->dst + (value - valid->src);
        return result;
    } else {
        return value;
    }
}

int main(void)
{
    char seeds_buf[IN_BUF_MAX];
    if (!fgets(seeds_buf, IN_BUF_MAX, stdin)) return 1;
    
    String_View seeds_sv = sv_lit(seeds_buf);
    seeds_sv = sv_trim_char_end(seeds_sv, '\n');
    
    //
    // Parse the seeds line.
    //
    
    const String_View seeds_prefix = sv_lit("seeds: ");
    assert(seeds_prefix.count < seeds_sv.count);
    
    String_View work_seeds_sv = seeds_sv;
    work_seeds_sv.vals  += seeds_prefix.count;
    work_seeds_sv.count -= seeds_prefix.count;
    
    // Seed seeds[SEEDS_MAX];
    Seed *seeds = malloc(SEEDS_MAX*sizeof(*seeds));
    size_t seed_count = 0;
    
    bool is_count = false;
    
    uint64_t seed = 0;
    String_View num_sv = {0};
    
    // TODO: allow switching between part 1 and 2
#if 1
    while (num_sv.vals < sv_end(work_seeds_sv)) {
        num_sv = sv_trim_to_next_char(&work_seeds_sv, ' ');
        if (num_sv.count < 1) continue;
        assert(sv_to_uint64_simple(num_sv, 10, &seed));
        assert(seed_count <= SEEDS_MAX);
        
        seeds[seed_count].id = seed;
        seeds[seed_count].value = seed;
        seed_count++;
    }
#else 
    
    uint64_t begin = 0;
    
    while (num_sv.vals < sv_end(work_seeds_sv)) {
        num_sv = sv_trim_to_next_char(&work_seeds_sv, ' ');
        if (num_sv.count < 1) continue;
        assert(sv_to_uint64_simple(num_sv, 10, &seed));
        assert(seed_count <= SEEDS_MAX);
        
        if (is_count) {
            assert(seed_count+seed <= SEEDS_MAX);
            for (size_t i = begin; i < begin+seed; ++i) {
                seeds[seed_count].id = i;
                seeds[seed_count].value = i;
                seed_count++;
            }
        } else {
            begin = seed;
        }
        
        // seeds[seed_count].id = seed;
        // seeds[seed_count].value = seed;
        // seed_count++;
        
        is_count = !is_count;
    }
    
    printf("SEED COUNT: %zu\n", seed_count);
    for (size_t i = 0; i < seed_count; ++i) {
        printf("%zu: %llu\n", i, seeds[i].value);
    }
#endif
    
    const String_View map_suffix = sv_lit(" map");
    
    Map maps[MAPS_MAX] = {0};
    size_t map_count = 0;
    
    Map *map = NULL;
    
    char line_buf[IN_BUF_MAX];
    
    // Map map = {0};
    // Range range = {0};
    while (fgets(line_buf, IN_BUF_MAX, stdin)) {
        String_View line_sv = sv_lit(line_buf);
        line_sv = sv_trim_char_end(line_sv, '\n');
        if (line_sv.count == 0) continue;
        
        char first = line_sv.vals[0];
        
        if (isalpha(first)) {
            assert(map_count <= MAPS_MAX);
            map = &maps[map_count++];
            
            String_View map_sv = line_sv;
            map->from = sv_trim_to_next_char(&map_sv, '-');
            // Swallow the 'to'.
            sv_trim_to_next_char(&map_sv, '-');
            map->to = sv_trim_to_next_char(&map_sv, '-');
            assert(map->from.count > 0 && map->to.count > map_suffix.count);
            map->to.count -= map_suffix.count;
            
            map->to = sv_trim_char_end(map->to, ' ');
            
            assert(map->from.count <= MAP_BUF_MAX);
            assert(map->to.count <= MAP_BUF_MAX);
            
            strncpy(map->from_buf, map->from.vals, map->from.count);
            strncpy(map->to_buf, map->to.vals, map->to.count);
            
            map->from.vals = map->from_buf;
            map->to.vals = map->to_buf;
            
            // printf("%.*s -> %.*s\n", sv_expand_for_printf(map->from), sv_expand_for_printf(map->to));
            
        } else if (isdigit(first)) {
            assert(map->from.vals);
            Range *range = &map->ranges[map->range_count++];
            
            String_View range_sv = line_sv;
            
            String_View dst_sv = sv_trim_to_next_char(&range_sv, ' ');
            String_View src_sv = sv_trim_to_next_char(&range_sv, ' ');
            String_View count_sv = sv_trim_to_next_char(&range_sv, ' ');
            assert(dst_sv.count && src_sv.count && count_sv.count);
            
            assert(sv_to_uint64_simple(dst_sv, 10, &range->dst));
            assert(sv_to_uint64_simple(src_sv, 10, &range->src));
            assert(sv_to_uint64_simple(count_sv, 10, &range->count));
            
            // printf("b: %llu, e: %llu, c: %llu\n", range->dst, range->src, range->count);
        } else {
            assert(false);
        }
        
    }
    
#if 0
    printf("seed count: %zu\n", seed_count);
    for (size_t i = 0; i < seed_count; ++i) {
        printf("-- Seed %zu: %llu\n", i, seeds[i]);
    }
    
    printf("\n");
    
    printf("map count: %zu\n", map_count);
    for (size_t i = 0; i < map_count; ++i) {
        Map *map = &maps[i];
        printf("-- Map %zu (%.*s -> %.*s)\n", i, 
               sv_expand_for_printf(map->from), 
               sv_expand_for_printf(map->to));
        
        for (size_t j = 0; j < map->range_count; ++j) {
            Range *range = &map->ranges[j];
            printf("---- Range %zu (dst=%llu src=%llu count=%llu)\n", j, range->dst, range->src, range->count);
        }
        
    }
#endif
    
    map = find_map_by_from(maps, map_count, sv_lit("seed"));
    assert(map);
    
    do {
#if 0
        printf("-- found: (%.*s -> %.*s)\n", 
               sv_expand_for_printf(map->from), 
               sv_expand_for_printf(map->to));
        
        for (size_t j = 0; j < map->range_count; ++j) {
            Range *range = &map->ranges[j];
            printf("---- Range %zu (dst=%llu src=%llu count=%llu)\n", j, range->dst, range->src, range->count);
        }
#endif
        
        for (size_t i = 0; i < seed_count; ++i) {
            Seed *seed = &seeds[i];
            
            uint64_t result = map_seed_value(map, seed->value);
            printf("%llu -> %llu\n", seed->value, result);
            seed->value = result;
        }
        printf("\n");
        
        if (sv_equal(map->to, sv_lit("location"))) break;
        
        map = find_map_by_from(maps, map_count, map->to);
        assert(map);
        
    } while (true);
    
    uint64_t min = UINT64_MAX;
    for (size_t i = 0; i < seed_count; ++i) {
        if (seeds[i].value < min) min = seeds[i].value;
        printf("%llu: %llu\n", seeds[i].id, seeds[i].value);
    }
    
    printf("BEST: %llu\n", min);
    
    return 0;
}