#include <iomanip>
#include <iostream>
#include <SlotMachine.hpp>

// Wide enough for the longest symbol name ("Scatter") plus a separating space
constexpr int SymbolColumnWidth = 8;

int main()
{
	SlotMachine* slotMachine = new SlotMachine();

	while (true)
	{
		int choice;
		std::cout << "Press 1 to spin the slot machine or 0 to exit: ";
		std::cin >> choice;

		if (choice == 0)
		{
			break;
		}

		SlotMachine::SpinResult result = slotMachine->spin();

		for (auto& i : result)
		{
			for (auto& j : i)
			{
				std::cout << std::left << std::setw(SymbolColumnWidth) << Symbol::getSymbolData(j).name;
			}

			std::cout << std::endl;
		}
	}

	return 0;
}