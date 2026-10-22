#pragma once
#include <string_view>

struct SymbolData
{
    std::string_view name;
    uint8_t weight;
    uint8_t multiplier;
};

namespace AppConfig
{
    inline constexpr uint8_t ReelCount;

    inline constexpr uint8_t TotalWeight = 20;

    inline constexpr SymbolData CherryData = {.name = "Cherry", .weight = 10, .multiplier = 3};
    inline constexpr SymbolData BellData = {.name = "Bell", .weight = 5, .multiplier = 5};
    inline constexpr SymbolData SevenData = {.name = "7", .weight = 1, .multiplier = 250};
    inline constexpr SymbolData WildData = {.name = "Wild", .weight = 2};
    inline constexpr SymbolData ScatterData = {.name = "Scatter", .weight = 2};
}