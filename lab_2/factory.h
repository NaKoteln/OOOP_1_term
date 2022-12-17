#ifndef LAB_2_FACTORY_H
#define LAB_2_FACTORY_H

#include "strategy.h"
#include "exceptions.h"
#include <string>
#include <functional>

class StrategyFactory {
private:
    std::map<std::string, std::function<StrategyBase* ()>> strategiesByNames;

public:
    ~StrategyFactory();

    template<typename T>
    void RegisterStrategy(std::string strategyName) {
        strategiesByNames[strategyName] = [strategyName] () -> StrategyBase* { return new T(strategyName); } ;
    }

    StrategyBase *GetStrategyByName(std::string &strategyName);

    std::vector<std::string> GetRegisteredStrategiesNames();
};


#endif //LAB_2_FACTORY_H
