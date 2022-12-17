#include <iostream>
#include "types.h"

#include "factory.h"

StrategyFactory* CreateStrategyFactoryWithStrategiesRegistered();

int main(int argC, char** argV) {
    auto factory = CreateStrategyFactoryWithStrategiesRegistered();

    try {
        auto parseResult = MyCmdParser::ParseCmdArgs(argC, argV);
        GameModeBase* gameModeBase;

        switch (parseResult.mode) {
            case FAST:
                gameModeBase = new CompetitionNoDetailsMode(factory, parseResult.strategiesNames, parseResult.steps, parseResult.matrix);
                break;
            case DETAILED:
                gameModeBase = new CompetitionWithDetailsMode(factory, parseResult.strategiesNames, parseResult.matrix);
                break;
            case TOURNAMENT:
                gameModeBase = new Tournament(factory, parseResult.strategiesNames, parseResult.steps, parseResult.matrix);
                break;
        }

        gameModeBase->Play();
        gameModeBase->PrintTotalScore();

        delete gameModeBase;
    } catch (std::exception& ex) {
        std::cerr << ex.what() << std::endl << std::endl;
        std::cerr << "List of known strategies:" << std::endl;
        for (auto &strategyName : factory->GetRegisteredStrategiesNames()) {
            std::cerr << "* " << strategyName << std::endl;
        }
    }

    delete factory;
    return 0;
}

StrategyFactory* CreateStrategyFactoryWithStrategiesRegistered() {
    auto factory = new StrategyFactory();

    // Simple
    factory->RegisterStrategy<AlwaysCooperateStrategy>("AlwaysCooperate");
    factory->RegisterStrategy<AlwaysDefectStrategy>("AlwaysDefect");
    factory->RegisterStrategy<AlwaysAlternateActionStrategy>("AlwaysAlternateAction");
    factory->RegisterStrategy<RandomActionStrategy>("RandomAction");

    // Complex
    factory->RegisterStrategy<MostUsedActionStrategy>("MostUsedAction");
    factory->RegisterStrategy<DefectIfAnyDefectStrategy>("DefectIfAnyDefect");
    factory->RegisterStrategy<MostUsedActionWithForgivenessStrategy>("MostUsedActionWithForgiveness");

    return factory;
}
