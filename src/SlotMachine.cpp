#include "SlotMachine.hpp"

SlotMachine::SlotMachine() : rngEngine_{ std::random_device{}() }
{
	
}

SlotMachine::SpinResult SlotMachine::spin()
{
	std::uniform_int_distribution<size_t> dist(0, reels_[0].getSize() - 1);

	SlotMachine::SpinResult spinResult{};

	for (size_t i = 0; i < AppConfig::ReelCount; i++)
	{
		size_t randomIndex = dist(rngEngine_);
		
		for (size_t j = 0; j < AppConfig::RowCount; j++)
		{
			spinResult[j][i] = reels_[i].getSymbolAt((randomIndex + j) % reels_[i].getSize());
		}
	}

	return spinResult;
}
