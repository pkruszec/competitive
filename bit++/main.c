// https://codeforces.com/problemset/problem/282/A
// solved

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

int main(void)
{
    int n;
    scanf("%d\n", &n);
    
    int64_t x = 0;
    
    char buf[32];
    for (int i = 0; i < n; ++i) {
        fgets(buf, sizeof(buf), stdin);
        size_t len = strlen(buf);
        if (buf[len-1] == '\n') len -= 1;
        
        switch (buf[0]) {
            case 'X':
            {
                if (buf[1] == '+') x++;
                else if (buf[1] == '-') x--;
            }break;
            
            case '+':
            {
                x++;
            }break;
            
            case '-':
            {
                x--;
            }break;
        }
        
    }
    
    printf("%lld", x);
    
    return 0;
}