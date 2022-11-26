#include <benchmark/benchmark.h>
#include <numeric>

#include "fractional.h"

void BM_ref_gcd (benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(details::gcd < std::int64_t > (state.range(0), 321));
        benchmark::ClobberMemory();
    }
}

void BM_binary_gcd(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(details::gcd < std::uint64_t > (state.range(0), 321));
        benchmark::ClobberMemory();
    }
}

// Register the function as a benchmark
#define GCD_RANGE Range(8, 8<<16)

BENCHMARK(BM_ref_gcd)->GCD_RANGE;
BENCHMARK(BM_binary_gcd)->GCD_RANGE;

BENCHMARK_MAIN();