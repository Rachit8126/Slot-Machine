#pragma once
#include "AppConfig.hpp"

class Symbol
{
private:
public:
    static const AppConfig::SymbolData &getSymbolData(AppConfig::SymbolType symbolType);
};