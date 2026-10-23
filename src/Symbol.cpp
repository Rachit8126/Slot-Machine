#include "Symbol.hpp"

AppConfig::SymbolData const &Symbol::getSymbolData(SymbolType symbolType)
{
    switch (symbolType)
    {
    case SymbolType::CHERRY:
        return AppConfig::CherryData;
    case SymbolType::BELL:
        return AppConfig::BellData;
    case SymbolType::SEVEN:
        return AppConfig::SevenData;
    case SymbolType::SCATTER:
        return AppConfig::ScatterData;
    case SymbolType::WILD:
        return AppConfig::WildData;
    }

    return AppConfig::CherryData;
}
