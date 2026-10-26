#include "Symbol.hpp"

AppConfig::SymbolData const &Symbol::getSymbolData(AppConfig::SymbolType symbolType)
{
    switch (symbolType)
    {
    case AppConfig::SymbolType::CHERRY:
        return AppConfig::CherryData;
    case AppConfig::SymbolType::BELL:
        return AppConfig::BellData;
    case AppConfig::SymbolType::SEVEN:
        return AppConfig::SevenData;
    case AppConfig::SymbolType::SCATTER:
        return AppConfig::ScatterData;
    case AppConfig::SymbolType::WILD:
        return AppConfig::WildData;
    }

    return AppConfig::CherryData;
}
