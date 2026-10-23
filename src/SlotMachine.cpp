
#include "SlotMachine.hpp"

SlotMachine::SlotMachine() : rngEngine_{ std::random_device{}() }
{
	
}

SlotMachine::SpinResult SlotMachine::spin()
{
	std::uniform_int_distribution<size_t> dist(0, AppConfig::TotalWeight - 1);

	SlotMachine::SpinResult spinResult{};

	for (size_t i = 0; i < AppConfig::ReelCount; i++)
	{
		size_t randomIndex = dist(rngEngine_);
		spinResult.at(i) = {
			reels_[i].getSymbolAt(randomIndex - 1 < 0 ? reels_[i].getSize() - 1 : randomIndex - 1),
			reels_[i].getSymbolAt(randomIndex),
			reels_[i].getSymbolAt(randomIndex + 1 >= reels_[i].getSize() ? 0 : randomIndex + 1)
		};
	}

	return spinResult;
}
