#include <iostream>
#include <string.h>

typedef int32_t bool32;
typedef int64_t bool64;

/*
struct Ant {
    int32_t pos;
    bool32 dir_is_right;
    uint32_t count;
};
*/

typedef uint8_t Cell_Type;
enum {
    Cell_None = 0,
    Cell_Left,
    Cell_Right,
};

struct Cell {
    Cell_Type type;
    int32_t id;
};

void repr_board(uint64_t board_size, Cell *cells)
{    
    // Repr board
    for (uint64_t i = 0;
         i < board_size;
         ++i)
    {
        Cell *cell = &cells[i];
        char repr = '.';
        if (cell->type == Cell_Left) repr = 'L';
        else if (cell->type == Cell_Right) repr = 'P';
        std::cout << repr;
    }
    std::cout << "\n";
}

int main(void)
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    uint64_t n = 0;
    std::cin >> n;
    if (!n) return 0;

    uint64_t padding = (n+10);
    uint64_t board_size = n + (2 * padding); 

    uint64_t *counts = new uint64_t[n];
    memset(counts, 0, n * sizeof(*counts));

    int8_t *done = new int8_t[n];
    memset(done, 0, n * sizeof(*done));

    Cell *cells = new Cell[board_size];
    memset(cells, 0, board_size * sizeof(*cells));

    for (uint64_t i = 0;
         i < n;
         ++i)
    {
        char dir_symbol = 0;
        std::cin >> dir_symbol;

        Cell *cell = &cells[i + padding];
        cell->type = (dir_symbol == 'P' ? Cell_Right : Cell_Left);
        cell->id = i;
    }

    // repr_board(board_size, cells);

    // test1: 6 -> 3


    for (int i = 0; i < n; ++i) {

        memset(done, 0, n * sizeof(*done));
        for (uint64_t i = 0;
             i < board_size;
             ++i)
        {
            Cell *cell = &cells[i];
            if (cell->type == Cell_None) continue;

            if (i == 0 && cell->type == Cell_Left) {
                cell->type = Cell_None;
                continue;
            }

            if (i == board_size - 1 && cell->type == Cell_Right) {
                cell->type = Cell_None;
                continue;
            }

            if (done[cell->id]) continue;

            uint64_t next_i = cell->type == Cell_Right ? (i + 1) : (i - 1);
            Cell *next = &cells[next_i];
            if (next->type != Cell_None && next->type != cell->type) {
                // NOTE(pkruszec): swap directions
                Cell_Type tmp = cell->type;
                cell->type = next->type;
                next->type = tmp;

                counts[cell->id]++;
                counts[next->id]++;

                done[cell->id] = true;
                done[next->id] = true;

                //next_i = cell->type == Cell_Right ? i + 1 : i - 1;
                //next = &cells[next_i];
            } else if (next->type == Cell_None) {
                next->type = cell->type;
                next->id = cell->id;

                cell->type = Cell_None;
                cell->id = 0;

                done[next->id] = true;
            }
        }
        // repr_board(board_size, cells);

    }

    // Repr counts
    for (uint64_t i = 0;
         i < n;
         ++i)
    {
        std::cout << counts[i] << " ";
    }
    std::cout << "\n";

    /*
    Ant *ants = new Ant[n];
    // TODO(pkruszec): does new zero out the memory?
    // maybe replace with malloc
    memset(ants, 0, n * sizeof(*ants));

    for (uint32_t i = 0;
         i < n;
         ++i)
    {
        Ant *ant = &ants[i];
        char dir_symbol = 0;
        std::cin >> dir_symbol;

        ant->dir_is_right = (dir_symbol == 'P');
    }

    for (uint32_t i = 0;
         i < n;
         ++i) 
    {
        Ant *ant = &ants[i];


    }
    */

    return 0;
}