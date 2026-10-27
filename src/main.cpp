#include <array>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "SlotMachine.hpp"
#include "Evaluator.hpp"
#include "Symbol.hpp"

namespace
{
	constexpr int SymbolColumnWidth = 8;

	void printPayLine(std::size_t lineIndex, const std::array<AppConfig::Position, AppConfig::ReelCount> &payLine)
	{
		const std::string label = std::to_string(lineIndex) + " -> ";
		const int middleRow = AppConfig::RowCount / 2;

		for (int row = 0; row < AppConfig::RowCount; ++row)
		{
			if (row == middleRow)
			{
				std::cout << label;
			}
			else
			{
				std::cout << std::string(label.size(), ' ');
			}

			for (int reel = 0; reel < AppConfig::ReelCount; ++reel)
			{
				const bool isOnLine = payLine[reel].row == row;

				std::cout << (isOnLine ? 'X' : '0') << (reel + 1 < AppConfig::ReelCount ? " " : "");
			}

			std::cout << "\n";
		}

		std::cout << "\n";
	}
}

int main()
{
	std::unique_ptr<SlotMachine> slotMachine = std::make_unique<SlotMachine>();

	while (true)
	{
		int choice;

		std::cout << "Press 1 to spin the slot machine or 0 to exit: ";
		std::cin >> choice;

		if (choice == 0)
		{
			break;
		}

		if (choice != 1)
		{
			break;
		}

		std::vector<std::size_t> activeLines;

		if (choice == 1)
		{
			std::cout << "Pay lines: " << "\n";

			for (std::size_t lineIndex = 0; lineIndex < AppConfig::PayLines.size(); ++lineIndex)
			{
				printPayLine(lineIndex, AppConfig::PayLines[lineIndex]);
			}

			std::string activeLinesInput;
			std::cout << "Enter the index of lines you want to place bet on, separating each line index by comma (1,2,3): ";
			std::cin >> activeLinesInput;

			std::stringstream lineStream(activeLinesInput);
			std::string token;

			while (std::getline(lineStream, token, ','))
			{
				std::istringstream tokenStream(token);
				std::size_t lineIndex;

				if ((tokenStream >> lineIndex) && lineIndex < AppConfig::PayLines.size())
				{
					activeLines.push_back(lineIndex);
				}
			}
		}

		SlotMachine::SpinResult result = slotMachine->spin();

		for (auto &i : result)
		{
			for (auto &j : i)
			{
				std::cout << std::left << std::setw(SymbolColumnWidth) << Symbol::getSymbolData(j).name;
			}

			std::cout << "\n";
		}

		SpinEvaluationResult spinResult = Evaluator::evaluate(result, activeLines);

		std::cout << "Total Win: " << (spinResult.totalMultiplier + spinResult.scatterWin) << "\n";
	}

	return 0;
}