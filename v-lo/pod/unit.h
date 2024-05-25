#ifndef UNIT_H
#define UNIT_H

//
// Logging
//

#ifndef UnitLog // Must support printf formatting.
# include <stdio.h>
# define UnitLog(...) fprintf(stderr, __VA_ARGS__)
#endif

#ifndef UNIT_TEST_PASSED_STRING
# define UNIT_TEST_PASSED_STRING "TEST PASSED: "
#endif
#ifndef UNIT_TEST_FAILED_STRING
# define UNIT_TEST_FAILED_STRING "TEST FAILED: "
#endif

#ifdef UNIT_LOG_PASSED
# define UnitLogPassed(...) UnitLog(UNIT_TEST_PASSED_STRING __VA_ARGS__)
#else
# define UnitLogPassed(...)
#endif

#define UnitLogFailed(...) UnitLog(UNIT_TEST_FAILED_STRING __VA_ARGS__)

//
// Utilities
//

#ifndef UnitArrayCount
# define UnitArrayCount(arr) (sizeof(arr) / sizeof((arr)[0]))
#endif

//
// Expects
//

#define Expect(x) \
    do { \
        if (x) { \
            UnitLogPassed(#x "\n"); \
        } else { \
            UnitLogFailed("Expected to be true: " #x "\n"); \
        } \
    } while (0)

#define ExpectEqual(exp, got, fmt) \
    do { \
        if ((exp) == (got)) { \
            UnitLogPassed(#got " == " #exp " (" fmt ")" "\n", exp); \
        } else { \
            UnitLogFailed("Expected " fmt ", got " fmt "\n", exp, got); \
        } \
    } while (0)

#endif /* UNIT_H */

#ifdef UNIT_IMPLEMENTATION
#endif /* UNIT_IMPLEMENTATION */
