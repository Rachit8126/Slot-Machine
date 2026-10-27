#include "Evaluator.hpp"

SpinEvaluationResult Evaluator::evaluate(const SlotMachine::SpinResult& spinResult)
{
	// Count Scatter symbols
	uint8_t scatterCount = 0;
	uint16_t scatterWin = 0;
	for (const auto& row : spinResult)
	{
		for (const auto& symbol : row)
		{
			if (symbol == AppConfig::SymbolType::SCATTER)
			{
				scatterCount++;
			}
		}
	}

	// Evaluating Scatter wins
	for (auto& i : AppConfig::PayTable)
	{
		if (i.symbolType != AppConfig::SymbolType::SCATTER)
		{
			continue;
		}

		if (scatterCount >= i.count)
		{
			scatterWin = i.multiplier;
		}
	}

	// Check with paylines in AppConfig::PayLines
	std::vector<LineWin> lineWins;

	for (auto& payLine : AppConfig::PayLines)
	{
		AppConfig::SymbolType firstSymbol = spinResult[payLine[0].row][payLine[0].reel];

		if (firstSymbol == AppConfig::SymbolType::SCATTER)
		{
			continue; // Skip scatter symbols for line wins
		}

		bool isWinningLine = true;

		for (size_t i = 1; i < payLine.size(); ++i)
		{
			AppConfig::SymbolType currentSymbol = spinResult[payLine[i].row][payLine[i].reel];
			if (currentSymbol != firstSymbol && currentSymbol != AppConfig::SymbolType::WILD)
			{
				isWinningLine = false;
				break;
			}
		}
	}
}