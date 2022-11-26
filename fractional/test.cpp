#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <cinttypes>

#include "fractional.h"

TEST_CASE("add", "fractional") {
	auto const VAL1			= fract(1.5);
	auto const VAL2			= fract(4.5);
	auto const EXPECTED		= double(6);

	auto res = static_cast <double> (VAL1 + VAL2);
	REQUIRE(EXPECTED == res);
}

TEST_CASE("add unsigned", "fractional") {
	auto const VAL1 = ufract(1.5);
	auto const VAL2 = ufract(4.5);
	auto const EXPECTED = double(6);

	auto res = static_cast <double> (VAL1 + VAL2);
	REQUIRE(EXPECTED == res);
}

TEST_CASE("add negative", "fractional") {
	auto const VAL1 = fract(-1.5);
	auto const VAL2 = fract(-14.5);
	auto const EXPECTED = double(-16);

	auto res = static_cast <double> (VAL1 + VAL2);
	REQUIRE(EXPECTED == res);
}

TEST_CASE("sub", "fractional") {
	auto const VAL1 = fract(56.7);
	auto const VAL2 = fract(7.56);
	auto const EXPECTED = double(49.14);

	auto res = static_cast <double> (VAL1 - VAL2);
	REQUIRE(EXPECTED == res);
}

TEST_CASE("sub unsigned", "fractional") {
	auto const VAL1 = fract(56.7);
	auto const VAL2 = fract(7.56);
	auto const EXPECTED = double(49.14);

	auto res = static_cast <double> (VAL1 - VAL2);
	REQUIRE(EXPECTED == res);
}

TEST_CASE("sub negative", "fractional") {
	auto const VAL1 = fract(7.56);
	auto const VAL2 = fract(56.7);
	auto const EXPECTED = double(-49.14);

	auto res = static_cast <double> (VAL1 - VAL2);
	REQUIRE(EXPECTED == res);
}