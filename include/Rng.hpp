#pragma once

#include <random>

using RngEngine = std::mt19937;

inline RngEngine makeSeededEngine()
{
    std::random_device rd;
    std::seed_seq seed{rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd()};
    return RngEngine(seed);
}