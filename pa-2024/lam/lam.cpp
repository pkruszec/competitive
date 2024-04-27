#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    Row = 0,
    Col = 1,
};

int n, m;
int nm;
char *sp_table;
char *pv_table;

#define AtN(t, x, y) ((t)[(y)*(n) + (x)])

static int
are_tables_equal(void)
{
    for (int i = 0; i < nm; ++i) {
        if (sp_table[i] != pv_table[i]) return false;
    }
    return true;
}

static void
fill_pv_line(int dimension, char value, int index_from_0)
{
    if (dimension == Col) {
        for (int y = 0; y < n; ++y) {
            AtN(pv_table, index_from_0, y) = value;
        }
    } else {
        for (int x = 0; x < m; ++x) {
            AtN(pv_table, x, index_from_0) = value;
        }
    }
}

int
main(void)
{
    scanf("%d %d\n", &n, &m);
    nm = n * m;

    // Init
    sp_table = (char *) malloc(nm * sizeof(*sp_table));
    pv_table = (char *) malloc(nm * sizeof(*pv_table));
    // Init to dots for better debugging
    memset(pv_table, '.', nm * sizeof(*pv_table));

    // Getting the input
    char tmp;
    for (int i = 0; i < nm; ++i) {
        scanf("%c", &sp_table[i]);
        if (i % m == (m-1)) scanf("%c", &tmp); // consume the new line
    }

    for (int y = 0; y < n; ++y) {
        for (int x = 0; x < m; ++x) {
            printf("%c", pv_table[y*n + x]);
        }
        printf("\n");
    }

    // If the row or column is fully in one color,
    // fill it at the end

    // Requirements:
    // sp_table = pv_table
    // move count <= n+m
    printf("equal: %d\n", are_tables_equal());
    return 0;
}