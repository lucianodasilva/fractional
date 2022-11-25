#include <benchmark/benchmark.h>
#include "fractional.h"

void BM_ref_gcd (benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(reference_gcd(state.range(0), 321));
        benchmark::ClobberMemory();
    }
}

void BM_binary_gcd(benchmark::State& state) {
    for (auto _ : state) {
        benchmark::DoNotOptimize(binary_gcd(state.range(0), 321));
        benchmark::ClobberMemory();
    }
}

// Register the function as a benchmark
#define GCD_RANGE Range(8, 8<<16)

BENCHMARK(BM_ref_gcd)->GCD_RANGE;
BENCHMARK(BM_binary_gcd)->GCD_RANGE;

BENCHMARK_MAIN();