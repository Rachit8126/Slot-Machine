#pragma once

#include <vector>
#include <cstddef>

#include "AppConfig.hpp"
#include "Rng.hpp"

class Reel
{
	using ReelVector = std::vector<AppConfig::SymbolType>;

private:
	ReelVector reel_;

public:
	explicit Reel(RngEngine &rngEngine);

	AppConfig::SymbolType getSymbolAt(size_t index) const
	{
		return reel_.at(index);
	}

	size_t getSize() const
	{
		return reel_.size();
	}
};