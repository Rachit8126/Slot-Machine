#pragma once
#include <Reel.hpp>
#include <array>
#include <random>

class SlotMachine
{
private:
    static constexpr uint8_t ReelCount = 3;

    std::mt19937 rngEngine_;
    std::array<Reel, ReelCount> reels_;

public:
    SlotMachine();

    using SpinResult = std::array<std::array<SymbolType, 3>, ReelCount>;

    SpinResult spin();
};