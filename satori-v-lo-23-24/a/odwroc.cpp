#include <iostream>

int main(void) {
    int a[100];
    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = n-1; i >= 0; --i) std::cout << a[i] << " ";
}
