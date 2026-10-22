#pragma once
#include <Reel.hpp>

class SlotMachine
{
private:
    constexpr int ReelCount = 3;

    std::vector<Reel> reels_;

public:
    SlotMachine();
};