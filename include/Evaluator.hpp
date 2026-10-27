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
	uint8_t multiplier;
};

struct SpinEvaluationResult
{
	std::vector<LineWin> lineWins;
	uint16_t scatterWin;
	uint16_t totalMultiplier;
};

class Evaluator
{
public:
	static SpinEvaluationResult evaluate(const SlotMachine::SpinResult&);
};