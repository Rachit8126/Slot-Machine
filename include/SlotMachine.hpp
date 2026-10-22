#pragma once
#include <Reel.hpp>
#include <array>

class SlotMachine
{
private:
    static constexpr uint8_t ReelCount = 3;

    using SpinResult = std::array<std::array<SymbolType, 3>, ReelCount>;

    std::array<Reel, ReelCount> reels_;

public:
    SlotMachine();

    SpinResult spin();
};