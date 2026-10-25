#include "Reel.hpp"
#include "AppConfig.hpp"
#include <array>
#include <numeric>
#include <random>

Reel::Reel(RngEngine &rng)
{
    static constexpr std::array<SymbolType, 5> symbolTypes = {
        SymbolType::CHERRY,
        SymbolType::BELL,
        SymbolType::SEVEN,
        SymbolType::WILD,
        SymbolType::SCATTER};

    reel_.resize(AppConfig::TotalWeight);

    std::vector<size_t> freeIndices(AppConfig::TotalWeight);
    std::iota(freeIndices.begin(), freeIndices.end(), 0);

    for (SymbolType type : symbolTypes)
    {
        const int weight = Symbol::getSymbolData(type).weight;

        for (int i = 0; i < weight && !freeIndices.empty(); i++)
        {
            std::uniform_int_distribution<size_t> pick(0, freeIndices.size() - 1);
            const size_t slot = pick(rng);

            reel_[freeIndices[slot]] = type;
            freeIndices[slot] = freeIndices.back();
            freeIndices.pop_back();
        }
    }
}
