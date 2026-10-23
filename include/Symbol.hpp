#pragma once
#include "AppConfig.hpp"

enum class SymbolType
{
    CHERRY,
    SEVEN,
    BELL,
    WILD,
    SCATTER
};

class Symbol
{
private:
public:
    static const AppConfig::SymbolData &getSymbolData(SymbolType symbolType);
};