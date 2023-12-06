#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "string_view.h"

typedef struct {
    uint64_t time;
    uint64_t record;
} Race;

#define RACES_MAX 32
#define LINE_MAX 256

uint64_t get_distance(Race race, uint64_t time_held)
{
    if (time_held >= race.time) return 0;
    
    uint64_t velocity = time_held;
    uint64_t time_left = race.time - time_held;
    return velocity * time_left;
}

int main(void)
{
    String_View times_prefix = sv_lit("Time:");
    String_View records_prefix = sv_lit("Distance:");
    
    bool part1 = false;
    
    if (part1) {
        //
        // Part 1.
        //
        
        Race races[RACES_MAX] = {0};
        size_t race_count = 0;
        
        char line[LINE_MAX];
        String_View current;
        size_t times_filled_count = 0;
        size_t records_filled_count = 0;
        
        //
        // Get and parse the times.
        //
        assert(fgets(line, LINE_MAX, stdin));
        
        String_View times = sv_lit(line);
        times = sv_trim_char_end(times, '\n');
        
        assert(times.count > times_prefix.count);
        times.vals += times_prefix.count;
        times.count -= times_prefix.count;
        
        current = (String_View) {0};
        while (current.vals < sv_end(times)) {
            current = sv_trim_to_next_char(&times, ' ');
            if (current.count < 1) continue;
            
            uint32_t time;
            assert(sv_to_uint32_simple(current, 10, &time));
            
            assert(times_filled_count < RACES_MAX);
            races[times_filled_count++].time = time;
        }
        
        
        //
        // Get and parse the records.
        //
        assert(fgets(line, LINE_MAX, stdin));
        String_View records = sv_lit(line);
        records = sv_trim_char_end(records, '\n');
        
        assert(records.count > records_prefix.count);
        records.vals += records_prefix.count;
        records.count -= records_prefix.count;
        
        current = (String_View) {0};
        while (current.vals < sv_end(records)) {
            current = sv_trim_to_next_char(&records, ' ');
            if (current.count < 1) continue;
            
            uint32_t record;
            assert(sv_to_uint32_simple(current, 10, &record));
            
            assert(records_filled_count < RACES_MAX);
            races[records_filled_count++].record = record;
        }
        
        assert(times_filled_count == records_filled_count);
        race_count = times_filled_count;
        
        size_t beat_product = 1;
        
        for (size_t i = 0; i < race_count; ++i) {
            uint32_t beat_count = 0;
            for (size_t j = 0; j < races[i].time; ++j) {
                if (get_distance(races[i], j) > races[i].record) ++beat_count;
            }
            
            if (beat_count) beat_product *= beat_count;
        }
        
        printf("PRODUCT: %zu\n", beat_product);
        
    } else {
        //
        // Part 2.
        //
        
        Race race = {0};
        char line[LINE_MAX];
        char num_buf[LINE_MAX] = {0};
        size_t num_buf_len;
        String_View temp;
        
        //
        // Get and parse the entire race time.
        //
        assert(fgets(line, LINE_MAX, stdin));
        String_View times = sv_lit(line);
        times = sv_trim_char_end(times, '\n');
        
        assert(times.count > times_prefix.count);
        times.vals += times_prefix.count;
        times.count -= times_prefix.count;
        
        num_buf_len = 0;
        for (size_t i = 0; i < times.count; ++i) {
            assert(num_buf_len < LINE_MAX);
            if (times.vals[i] != ' ')
                num_buf[num_buf_len++] = times.vals[i];
        }
        temp = sv_lit(num_buf);
        assert(sv_to_uint64_simple(temp, 10, &race.time));
        
        printf("TIME: %llu\n", race.time);
        
        //
        // Get and parse the entire race record.
        //
        assert(fgets(line, LINE_MAX, stdin));
        String_View records = sv_lit(line);
        records = sv_trim_char_end(records, '\n');
        
        assert(records.count > records_prefix.count);
        records.vals += records_prefix.count;
        records.count -= records_prefix.count;
        
        num_buf_len = 0;
        
        num_buf_len = 0;
        for (size_t i = 0; i < records.count; ++i) {
            assert(num_buf_len < LINE_MAX);
            if (records.vals[i] != ' ')
                num_buf[num_buf_len++] = records.vals[i];
        }
        temp = sv_lit(num_buf);
        assert(sv_to_uint64_simple(temp, 10, &race.record));
        
        printf("RECORD: %llu\n", race.record);
        
        uint64_t beat_count = 0;
        for (size_t i = 0; i < race.time; ++i) {
            if (get_distance(race, i) > race.record) ++beat_count;
        }
        
        printf("BEAT COUNT: %llu\n", beat_count);
    }
    
    return 0;
}