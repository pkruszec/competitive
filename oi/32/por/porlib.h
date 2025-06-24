#ifndef PORLIB_H
#define PORLIB_H

#include <cstdint>
#include <iostream>
#include <stdexcept>

class __PorLib {
private:
    bool initialized = false;
    size_t n;

    void initialize() {
        if (!initialized) {
            std::cin >> n;
            initialized = true;
        }
    }

public:
    size_t get_N() {
        if (!initialized) {
            initialize();
        }
        return n;
    }

    uint64_t swap_and_get_inversions(size_t a, size_t b) {
        if (!initialized) {
            initialize();
        }
        std::cout << a << ' ' << b << std::endl;
        uint64_t result;
        std::cin >> result;
        return result;
    }
};

// Singleton instance
static __PorLib __some_class_object;

// Public API
inline int DajN() {
    return (int)__some_class_object.get_N();
}

inline int Zamiana(int a, int b) {
    return (int)__some_class_object.swap_and_get_inversions(a, b);
}

#endif // PORLIB_H
