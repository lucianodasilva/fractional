#pragma once

#include <iostream>

inline intptr_t reference_gcd(intptr_t const a, intptr_t const b) {
	if (b == 0)
		return a;

	return reference_gcd(b, a % b);
}

inline uintptr_t binary_gcd(uintptr_t u, uintptr_t v) {

    if (u == 0)
        return v;

    if (v == 0)
        return u;

    auto shift = _BitScanForward64(u | v);
    u >>= __builtin_ctz(u);

    do {
        v >>= __builtin_ctz(v);
        v -= u;
        auto m = v >> 31;
        u += v & m;
        v = (v + m) ^ m;
    } while (v != 0);

    return u << shift;
}


struct fract {
public:



};