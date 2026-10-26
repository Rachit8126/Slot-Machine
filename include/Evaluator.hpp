#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

#include "AppConfig.hpp"

struct LineWin
{
	size_t lineIndex;
	AppConfig::SymbolType symbolType;
	uint8_t multiplier;
};

struct SpinEvaluationResult
{
	std::vector<LineWin> lineWins;
	uint32_t scatterWin;
	uint32_t totalMultiplier;
};

class Evaluator
{
public:
	static SpinEvaluationResult evaluateSpin(const std::array<std::array<AppConfig::SymbolType, AppConfig::ReelCount>, AppConfig::RowCount> &spinResult);
};