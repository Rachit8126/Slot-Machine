#pragma once
#include <array>
#include <random>

#include "Reel.hpp"

class SlotMachine
{
private:
    std::mt19937 rngEngine_;
    std::array<Reel, AppConfig::ReelCount> reels_;

public:
    SlotMachine();

    using SpinResult = std::array<std::array<SymbolType, AppConfig::ReelCount>, AppConfig::RowCount>;

    SpinResult spin();
};