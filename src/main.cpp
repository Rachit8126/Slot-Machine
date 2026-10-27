#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "SlotMachine.hpp"
#include "Evaluator.hpp"
#include "Symbol.hpp"
#include "Wallet.hpp"

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

	bool readLine(const std::string &prompt, std::string &output)
	{
		std::cout << prompt;

		return static_cast<bool>(std::getline(std::cin, output));
	}

	bool parseInt(const std::string &input, int64_t &value)
	{
		std::istringstream stream(input);
		char extra;

		if (!(stream >> value))
		{
			return false;
		}

		return !(stream >> extra);
	}

	// Parses "1,2,3" into a sorted, de-duplicated list of valid line indices.
	std::vector<std::size_t> parseLines(const std::string &input, std::size_t &ignoredCount)
	{
		std::vector<std::size_t> lines;
		std::stringstream lineStream(input);
		std::string token;

		ignoredCount = 0;

		while (std::getline(lineStream, token, ','))
		{
			int64_t lineIndex;

			if (parseInt(token, lineIndex) && lineIndex >= 0 && static_cast<std::size_t>(lineIndex) < AppConfig::PayLines.size())
			{
				lines.push_back(static_cast<std::size_t>(lineIndex));
			}
			else
			{
				++ignoredCount;
			}
		}

		std::sort(lines.begin(), lines.end());

		const std::size_t uniqueCount = std::unique(lines.begin(), lines.end()) - lines.begin();
		ignoredCount += lines.size() - uniqueCount;
		lines.resize(uniqueCount);

		return lines;
	}
}

int main()
{
	std::unique_ptr<SlotMachine> slotMachine = std::make_unique<SlotMachine>();
	std::unique_ptr<Wallet> wallet = std::make_unique<Wallet>(1000);

	while (true)
	{
		std::string input;
		int64_t choice;

		std::cout << "Balance: " << wallet->getBalance() << "\n";

		if (!readLine("Press 1 to spin the slot machine or 0 to exit: ", input))
		{
			break;
		}

		if (!parseInt(input, choice) || (choice != 0 && choice != 1))
		{
			std::cout << "Invalid choice!" << "\n";
			continue;
		}

		if (choice == 0)
		{
			break;
		}

		std::cout << "Pay lines: " << "\n";

		for (std::size_t lineIndex = 0; lineIndex < AppConfig::PayLines.size(); ++lineIndex)
		{
			printPayLine(lineIndex, AppConfig::PayLines[lineIndex]);
		}

		int64_t bet;

		if (!readLine("Per line bet: ", input))
		{
			break;
		}

		if (!parseInt(input, bet) || bet <= 0)
		{
			std::cout << "Bet must be a positive number!" << "\n";
			continue;
		}

		if (!readLine("Enter the index of lines you want to place bet on, separating each line index by comma (1,2,3): ", input))
		{
			break;
		}

		std::size_t ignoredCount;
		const std::vector<std::size_t> activeLines = parseLines(input, ignoredCount);

		if (ignoredCount > 0)
		{
			std::cout << "Ignored " << ignoredCount << " invalid or duplicate line(s)." << "\n";
		}

		if (activeLines.empty())
		{
			std::cout << "Select at least one valid line!" << "\n";
			continue;
		}

		const int64_t lineCount = static_cast<int64_t>(activeLines.size());

		if (bet > std::numeric_limits<int64_t>::max() / lineCount)
		{
			std::cout << "Bet too large!" << "\n";
			continue;
		}

		const int64_t totalBet = bet * lineCount;

		if (!wallet->debit(totalBet))
		{
			std::cout << "Not enough balance!" << "\n";
			continue;
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

		// Line wins pay on the per-line bet; scatter pays on the total bet.
		const int64_t totalWin = static_cast<int64_t>(spinResult.totalMultiplier) * bet + static_cast<int64_t>(spinResult.scatterWin) * totalBet;

		if (!wallet->credit(totalWin))
		{
			std::cout << "Could not credit winnings!" << "\n";
		}

		std::cout << "Total Win: " << totalWin << "\n";
	}

	return 0;
}
