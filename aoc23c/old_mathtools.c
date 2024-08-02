// Advent of Code 2023
// Dr Lee A. Christie
// @0x1ac@techhub.social

#include "old_mathtools.h"

#include <assert.h>

static long _old_gcd(long, long);

static long _old_gcd(long a, long b) {
    if (a == 0)
        return b;
    if (b == 0)
        return a;
    return _old_gcd(b, a % b);
}

long old_gcd(long a, long b) {
    assert(a > 0 && b > 0);
    return _old_gcd(a, b);
}

long old_lcm(long a, long b) {
    assert(a > 0 && b > 0);
    return (a * b) / old_gcd(a, b);
}
