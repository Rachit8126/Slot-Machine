#include "Evaluator.hpp"

namespace
{
	uint32_t findMultiplier(AppConfig::SymbolType symbolType, size_t count)
	{
		for (const auto &entry : AppConfig::PayTable)
		{
			if (entry.symbolType == symbolType && entry.count == count)
			{
				return entry.multiplier;
			}
		}

		return 0;
	}
}

SpinEvaluationResult Evaluator::evaluate(const SlotMachine::SpinResult &spinResult)
{
	SpinEvaluationResult result{};

	// Count Scatter symbols
	uint8_t scatterCount = 0;
	for (const auto &row : spinResult)
	{
		for (const auto &symbol : row)
		{
			if (symbol == AppConfig::SymbolType::SCATTER)
			{
				scatterCount++;
			}
		}
	}

	// Evaluating Scatter wins
	result.scatterWin = findMultiplier(AppConfig::SymbolType::SCATTER, scatterCount);

	// Check with paylines in AppConfig::PayLines
	for (size_t lineIndex = 0; lineIndex < AppConfig::PayLines.size(); ++lineIndex)
	{
		const auto &payLine = AppConfig::PayLines[lineIndex];

		// Resolve the line's symbol: the first non-wild symbol (WILD if all are wild)
		AppConfig::SymbolType target = AppConfig::SymbolType::WILD;
		for (const auto &pos : payLine)
		{
			AppConfig::SymbolType symbol = spinResult[pos.row][pos.reel];

			if (symbol != AppConfig::SymbolType::WILD)
			{
				target = symbol;
				break;
			}
		}

		if (target == AppConfig::SymbolType::SCATTER)
		{
			continue; // Skip scatter symbols for line wins
		}

		bool isWinningLine = true;
		for (const auto &pos : payLine)
		{
			AppConfig::SymbolType symbol = spinResult[pos.row][pos.reel];

			if (symbol != target && symbol != AppConfig::SymbolType::WILD)
			{
				isWinningLine = false;
				break;
			}
		}

		if (isWinningLine)
		{
			uint32_t multiplier = findMultiplier(target, payLine.size());

			if (multiplier > 0)
			{
				result.lineWins.push_back({lineIndex, target, multiplier});
			}
		}
	}

	// Total
	result.totalMultiplier = result.scatterWin;
	for (const auto &win : result.lineWins)
	{
		result.totalMultiplier += win.multiplier;
	}

	return result;
}
