#pragma once

#include <vector>
#include <Symbol.hpp>

class Reel
{
    using ReelVector = std::vector<SymbolType>;

private:
    ReelVector reel_;

public:
    Reel();

	SymbolType getSymbolAt(size_t index) const
	{
		return reel_.at(index);
	}

	size_t getSize() const
	{
		return reel_.size();
	}
};