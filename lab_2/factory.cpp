#include <cassert>
#include "factory.h"

StrategyBase *StrategyFactory::GetStrategyByName(std::string &strategyName) {
    auto it = strategiesByNames.find(strategyName);
    if (it == strategiesByNames.end()) { // strategy not found
        throw StrategyNotFoundException(strategyName);
    }
    return it->second();
}

StrategyFactory::~StrategyFactory() {
    for (auto it = strategiesByNames.begin(); it != strategiesByNames.end();) {
        it = strategiesByNames.erase(it);
    }
    assert(strategiesByNames.empty());
}

std::vector<std::string> StrategyFactory::GetRegisteredStrategiesNames() {
    std::vector<std::string> result;

    for (auto &strategyWithName: strategiesByNames) {
        result.push_back(strategyWithName.first);
    }

    return result;
}
