#include <iomanip>
#include <iostream>
#include <memory>

#include "SlotMachine.hpp"
#include "Evaluator.hpp"
#include "Symbol.hpp"

constexpr int SymbolColumnWidth = 8;

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

		SlotMachine::SpinResult result = slotMachine->spin();

		for (auto &i : result)
		{
			for (auto &j : i)
			{
				std::cout << std::left << std::setw(SymbolColumnWidth) << Symbol::getSymbolData(j).name;
			}

			std::cout << "\n";
		}

		SpinEvaluationResult spinResult = Evaluator::evaluate(result);

		std::cout << "Total Win: " << spinResult.totalMultiplier << "\n";
	}

	return 0;
}