#include <utility>

#include "SlotMachine.hpp"

SlotMachine::SlotMachine(RngEngine engine) : rngEngine_{std::move(engine)}
{
	reels_.reserve(AppConfig::ReelCount);
	for (size_t i = 0; i < AppConfig::ReelCount; i++)
	{
		reels_.emplace_back(rngEngine_);
	}
}

SlotMachine::SpinResult SlotMachine::spin()
{
	SlotMachine::SpinResult spinResult{};

	for (size_t i = 0; i < AppConfig::ReelCount; i++)
	{
		std::uniform_int_distribution<size_t> dist(0, reels_[i].getSize() - 1);

		size_t randomIndex = dist(rngEngine_);

		for (size_t j = 0; j < AppConfig::RowCount; j++)
		{
			spinResult[j][i] = reels_[i].getSymbolAt((randomIndex + j) % reels_[i].getSize());
		}
	}

	return spinResult;
}
