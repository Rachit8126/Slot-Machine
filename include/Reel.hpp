#pragma once

#include <vector>
#include <Symbol.hpp>

class Reel
{
    using ReelVector = std::vector<SymbolType>;

private:
    ReelVector reel_;

public:
    Reel();
};