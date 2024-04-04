#include <iostream>
#include <fstream>

// test1.txt -- 11
// test2.txt -- 8
// test3.txt -- 15
//
// Podejścia:
// 1. Podejście testowe (wynik: 0)
//

int main(int num_args, char **args) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

#ifdef POD_DEBUG
    char const *filename = 0;
    if (num_args < 2) {
        filename = "test1.txt";
    } else {
        filename = args[1];
    }

    std::ifstream in(filename);
    std::cin.rdbuf(in.rdbuf());
#endif

    int count = 0;
    int num_parts = 0;
    std::cin >> count >> num_parts;

    int *data = new int[count];

    int max = 0;
    for (int i = 0; i < count; ++i) {
        int current;
        std::cin >> current;
        data[i] = current;
        if (current > max) max = current;
    }

    //
    // TODO: Liczenie z prawej i z lewej, wybrać wartość najmniejszą
    // TODO: Jako początkowy s ustawić max(max, suma/num_num_parts)
    //

    int num_divs = num_parts - 1;

    int s = max;
    while (true) {
        int sum = 0;
        int divs_made = 0;
        bool valid = true;
        for (int i = 0; i < count; ++i) {
            sum += data[i];
            if (sum > s) {
                divs_made++;

                sum = data[i];
                if (sum > s) {
                    divs_made++;
                }
            }
            if (divs_made > num_divs) {
                valid = false;
                break;
            }
        }

        if (valid) {
            break;
        } else {
            s++;
        }

    }

    std::cout << s;

    return 0;
}
