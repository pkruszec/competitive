// https://codeforces.com/problemset/problem/1886/A
// not solved

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define true 1
#define false 0

typedef uint64_t u64;
typedef uint32_t u32;
typedef int32_t b32;

static inline b32 is_valid(u64 x, u64 y, u64 z)
{
    return (x != y && x != z && y != z) && (x % 3 != 0 && y % 3 != 0 && z % 3 != 0);
}

int main(void)
{
    u32 t;
    scanf("%u", &t);
    
    for (u32 ti = 0; ti < t; ++ti) {
        u64 a;
        scanf("%llu", &a);
        
        // x != y != z
        // x, y, z % 3 != 0
        
        u64 x = 0;
        u64 y = 0;
        u64 z = 0;
        b32 found = false;
        
#if 1
        for (u64 i = 1; i < a; ++i) {
            if (i % 3 == 0) continue;
            u64 max_i = a - i + 1;
            for (u64 j = 1; j < max_i; ++j) {
                if (j % 3 == 0 || j == i) continue;
                
                u64 max_j = max_i - j;
                
                for (u64 k = 1; k < max_j; ++k) {
                    if (k % 3 == 0 || k == j || k == i) continue;
                    
                    if (i + j + k != a) continue;
                    // if (i == j || i == k || j == k) continue;
                    
                    x = i;
                    y = j;
                    z = k;
                    found = true;
                    goto done;
                }
            }
        }
#elif 0
        u64 d = a / 3;
        u64 r = a % 3;
        
        x = d+r;
        y = d;
        z = d;
        
        while (y > 0 && (x == y || x % 3 == 0 || y % 3 == 0)) {
            x++;
            y--;
            
            // printf("%llu %llu %llu\n", x, y, z);
        }
        
        if (x % 3 == 0) goto done;
        
        while (z > 0 && (x == z || y == z || y % 3 == 0 || z % 3 == 0)) {
            // printf("%llu %llu %llu\n", x, y, z);
            
            y++;
            z--;
        }
        
        found = is_valid(x, y, z);
        
#else
        u64 d = a / 3;
        u64 r = a % 3;
        
        u64 ox = d+r;
        u64 oy = d;
        u64 oz = d;
        
        x = ox;
        y = oy;
        z = oz;
        
        // x, y
        
        while (x > 0) {
            x--;
            y++;
            if (is_valid(x, y, z)) {
                found = true;
                goto done;
            }
        }
        
        x = ox;
        y = oy;
        z = oz;
        while (y > 0) {
            x++;
            y--;
            if (is_valid(x, y, z)) {
                found = true;
                goto done;
            }
        }
        
        x = ox;
        y = oy;
        z = oz;
        
        // x, z
        while (x > 0) {
            x--;
            z++;
            if (is_valid(x, z, z)) {
                found = true;
                goto done;
            }
        }
        
        x = ox;
        y = oy;
        z = oz;
        while (z > 0) {
            x++;
            z--;
            if (is_valid(x, z, z)) {
                found = true;
                goto done;
            }
        }
        
        x = ox;
        y = oy;
        z = oz;
        // y, z
        while (y > 0) {
            y--;
            z++;
            if (is_valid(x, y, z)) {
                found = true;
                goto done;
            }
        }
        x = ox;
        y = oy;
        z = oz;
        while (z > 0) {
            y++;
            z--;
            if (is_valid(x, y, z)) {
                found = true;
                goto done;
            }
        }
        
        /*
4

2 1 1

3 0 1
1 2 1

3 1 0
1 1 2

2 1 0
2 0 1

*/
#endif
        done:
        
        if (found) {
            printf("YES\n");
            printf("%llu %llu %llu\n", x, y, z);
        } else {
            printf("NO\n");
        }
    }
    
    return 0;
}

