#ifndef LAB_2_TOURNAMENT_H
#define LAB_2_TOURNAMENT_H

#include "../gamemode.h"

class Tournament : public GameModeBase {
private:
    StrategyFactory * factory;
    std::vector<std::string> strategiesNames;
    std::map<std::string, int> strategiesScores;
    GameMatrix gameMatrix;
    int steps;

public:
    Tournament(StrategyFactory *factory, std::vector<std::string> &strategiesNames, int steps, GameMatrix &matrix) {
        this->factory = factory;
        this->strategiesNames = strategiesNames;
        this->gameMatrix = matrix;
        this->steps = steps;
    }

    void Play() override;

    Pairs GetTotalScore() override;

    void PrintTotalScore() override;
};

#endif //LAB_2_TOURNAMENT_H
