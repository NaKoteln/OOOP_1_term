#ifndef LAB_2_COMPETITIONWITHDETAILS_H
#define LAB_2_COMPETITIONWITHDETAILS_H

#include "../gamemode.h"

class CompetitionWithDetailsMode : public GameModeBase {
private:
    Simulator *simulator;

public:
    CompetitionWithDetailsMode(StrategyFactory* factory, std::vector<std::string> &strategiesNames, GameMatrix &matrix) {
        simulator = new Simulator(*factory, strategiesNames, matrix);
    }

    ~CompetitionWithDetailsMode() override { delete simulator; }

    void Play() override;

    Pairs GetTotalScore() override;

    void PrintTotalScore() override;
};

#endif //LAB_2_COMPETITIONWITHDETAILS_H
