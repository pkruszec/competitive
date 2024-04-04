#include <iostream>
#include <fstream>

int main(void) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

#if POD_DEBUG
    std::ifstream in("test1.txt");
    std::cin.rdbuf(in.rdbuf());
#endif

    int count = 0;
    int num_divs = 0;
    std::cin >> count >> num_divs;

    for (int i = 0; i < count; ++i) {
        int current;
        std::cin >> current;
    }
    
    return 0;
}
