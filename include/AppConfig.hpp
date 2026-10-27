#pragma once
#include <array>
#include <cstdint>
#include <string_view>

namespace AppConfig
{
	enum class SymbolType
	{
		CHERRY,
		SEVEN,
		BELL,
		WILD,
		SCATTER
	};

	struct SymbolData
	{
		std::string_view name;
		std::uint8_t weight;
	};

	struct PayEntry
	{
		SymbolType symbolType;
		std::uint8_t count;
		std::uint32_t multiplier;
	};

	struct Position
	{
		std::uint8_t row;
		std::uint8_t reel;
	};

	inline constexpr std::uint8_t ReelCount = 3;
	inline constexpr std::uint8_t RowCount = 3;

	inline constexpr std::uint8_t TotalWeight = 20;

	inline constexpr SymbolData CherryData = {.name = "Cherry", .weight = 11};
	inline constexpr SymbolData BellData = {.name = "Bell", .weight = 5};
	inline constexpr SymbolData SevenData = {.name = "7", .weight = 1};
	inline constexpr SymbolData WildData = {.name = "Wild", .weight = 2};
	inline constexpr SymbolData ScatterData = {.name = "Scatter", .weight = 1};

	inline constexpr std::array<PayEntry, 7> PayTable = {{{.symbolType = SymbolType::CHERRY, .count = 3, .multiplier = 3},
														  {.symbolType = SymbolType::BELL, .count = 3, .multiplier = 5},
														  {.symbolType = SymbolType::WILD, .count = 3, .multiplier = 10},
														  {.symbolType = SymbolType::SEVEN, .count = 3, .multiplier = 250},
														  {.symbolType = SymbolType::SCATTER, .count = 3, .multiplier = 5},
														  {.symbolType = SymbolType::SCATTER, .count = 2, .multiplier = 3},
														  {.symbolType = SymbolType::SCATTER, .count = 1, .multiplier = 1}}};

	inline constexpr std::array<std::array<Position, ReelCount>, 5> PayLines = {{{{{.row = 0, .reel = 0}, {.row = 0, .reel = 1}, {.row = 0, .reel = 2}}},
																				 {{{.row = 1, .reel = 0}, {.row = 1, .reel = 1}, {.row = 1, .reel = 2}}},
																				 {{{.row = 2, .reel = 0}, {.row = 2, .reel = 1}, {.row = 2, .reel = 2}}},
																				 {{{.row = 0, .reel = 0}, {.row = 1, .reel = 1}, {.row = 2, .reel = 2}}},
																				 {{{.row = 2, .reel = 0}, {.row = 1, .reel = 1}, {.row = 0, .reel = 2}}}}};
}