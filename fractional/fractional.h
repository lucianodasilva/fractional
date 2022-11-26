#pragma once

#include <iostream>
#include <type_traits>
#include <tuple>

namespace details {

#if defined (__GNUC__) || defined (__clang__)
    inline uint8_t count_tzb(std::size_t v) noexcept {
#	if defined (SGC_ARCH_X64)
        return static_cast <uint8_t> (__builtin_ctzl(v));
#	else
        return static_cast <uint8_t> (__builtin_ctz(v));
#	endif
    }
#elif defined (_MSC_VER)
    inline uint8_t count_tzb(std::uintmax_t v) noexcept {
        unsigned long c{ 0 };

#if defined (__x86_64__) || defined (_M_X64)
        _BitScanForward64(&c, v);
#else
        _BitScanForward(&c, v);
#endif

        return static_cast <uint8_t> (c);
    }
#endif

    template < typename T >
    using enable_if_integer = std::enable_if_t < std::is_integral_v < T > && std::is_signed_v < T > && !std::is_same_v < T, bool >, int >;

    template < typename T >
    using enable_if_uinteger = std::enable_if_t < std::is_integral_v < T >&& std::is_unsigned_v < T > && !std::is_same_v < T, bool >, int >;

    template < typename T >
    using enable_if_floating_point = std::enable_if_t < std::is_floating_point_v < T >, int >;

    template < typename T >
    inline T gcd(T lhv, T rhv, enable_if_integer < T > = {}) noexcept {
        while (rhv != 0) {
            auto mod_v = lhv % rhv;
            lhv = rhv;
            rhv = mod_v;
        }

        return lhv;
    }

    template < typename T >
    inline T gcd(T lhv, T rhv, enable_if_uinteger < T > = {}) noexcept {
        if (lhv == 0)
            return rhv;

        if (rhv == 0)
            return lhv;

        auto shift_u = count_tzb(lhv);
        auto shift_v = count_tzb(rhv);

        auto shift = std::min(shift_u, shift_v);

        lhv >>= shift_u;
        rhv >>= shift_v;

        for (;;) {
            if (lhv > rhv) {
                std::swap(lhv, rhv);
            }

            rhv -= lhv;

            if (rhv == 0) {
                return lhv << shift;
            }

            rhv >>= count_tzb(rhv);
        }
    }

    template < typename T >
    inline T lcm(T lhv, T rhv) {
        return rhv * (lhv / gcd(lhv, rhv));
    }

}

template < typename T >
struct basic_fract {
public:

    basic_fract() = default;
    
    inline basic_fract(T num, T den = 1) :
        _num(num),
        _den(den)
    {}

    template < typename U >
    inline explicit basic_fract(U fp_value, T basic_fractional_precision = 10000, details::enable_if_floating_point < U > = {}) {
        auto integral = std::floor(fp_value);
        auto basic_fractional = fp_value - integral;

        auto round_large_basic_fractional = static_cast <T> (std::round(basic_fractional * basic_fractional_precision));

        auto gcd_val = details::gcd(round_large_basic_fractional, basic_fractional_precision);

        _den = basic_fractional_precision / gcd_val;
        _num = (round_large_basic_fractional / gcd_val) + (_den * static_cast <T> (integral));
    }

    inline explicit operator double() const {
        auto simple = simplify();
        return double(_num) / double(_den);
    }

    inline bool operator == (basic_fract const& other) const { return _num == other._num && _den == other._den; }
    inline bool operator != (basic_fract const& other) const { return _num != other._num || _den != other._den; }

    inline bool operator < (basic_fract const& other) const {
        auto eq = make_equivalent(*this, other);
        return eq.first._num < eq.second._num;
    }

    inline bool operator > (basic_fract const& other) const {
        auto eq = make_equivalent(*this, other);
        return eq.first._num > eq.second._num;
    }

    inline bool operator <= (basic_fract const& other) const { return this->operator < (other) || this->operator == (other); }
    inline bool operator >= (basic_fract const& other) const { return this->operator > (other) || this->operator == (other); }

    inline basic_fract operator + (basic_fract const & other) const {
        auto eq = make_equivalent(*this, other);
        return { eq.first._num + eq.second._num, eq.first._den };
    }

    inline basic_fract& operator += (basic_fract const& other) {
        *this = this->operator + (other);
        return *this;
    }

    inline basic_fract operator - (basic_fract const & other) const {
        auto eq = make_equivalent(*this, other);
        return { eq.first._num - eq.second._num, eq.first._den };
    }

    inline basic_fract & operator -= (basic_fract const & other) {
        *this = this->operator - (other);
        return *this;
    }

    inline basic_fract operator * (basic_fract const & other) const {
        return { _num * other._num, _den * other._den };
    }

    inline basic_fract& operator *= (basic_fract const& other) {
        *this = this->operator *(other);
        return *this;
    }

    inline basic_fract operator * (T m) const {
        return {
            _num * m,
            _den * m
        };
    }

    inline basic_fract & operator *= (T m) {
        *this = this->operator *(m);
        return *this;
    }

    inline basic_fract operator / (basic_fract const& other) const {
        return { _num / other._num, _den / other._den };
    }

    inline basic_fract & operator / (basic_fract const & other) {
        *this = this->operator / (other);
        return *this;
    }

    inline static T lcd(basic_fract const& lhv, basic_fract const& rhv) {
        return details::lcm(lhv._den, rhv._den);
    }

    inline static std::pair < basic_fract, basic_fract > make_equivalent (basic_fract const& lhv, basic_fract const& rhv) {
        auto m = lcd(lhv, rhv);

        auto lhm = m / lhv._den;
        auto rhm = m / rhv._den;

        return { lhv * lhm, rhv * rhm };
    }

    inline basic_fract simplify() const {
        auto m = details::gcd(_num, _den);
        return { _num / m, _den / m };
    }

private:
    T _num{ 0 };
    T _den{ 0 };
};

using fract = basic_fract < std::intmax_t >;
using ufract = basic_fract < std::uintmax_t >;