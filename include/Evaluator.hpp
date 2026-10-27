#pragma once
#include <cstddef>
#include <cstdint>
#include <vector>

#include "AppConfig.hpp"
#include "SlotMachine.hpp"

struct LineWin
{
	size_t lineIndex;
	AppConfig::SymbolType symbolType;
	uint32_t multiplier;
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
	static SpinEvaluationResult evaluate(const SlotMachine::SpinResult &);
};