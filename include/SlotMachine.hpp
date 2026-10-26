#pragma once
#include <vector>
#include <array>
#include <random>

#include "Reel.hpp"
#include "Rng.hpp"
#include "AppConfig.hpp"

class SlotMachine
{
private:
    RngEngine rngEngine_;
    std::vector<Reel> reels_;

public:
    explicit SlotMachine(RngEngine rngEngine = makeSeededEngine());

    using SpinResult = std::array<std::array<AppConfig::SymbolType, AppConfig::ReelCount>, AppConfig::RowCount>;

    SpinResult spin();
};