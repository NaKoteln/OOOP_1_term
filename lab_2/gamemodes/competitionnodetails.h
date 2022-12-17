#ifndef LAB_2_COMPETITIONNODETAILS_H
#define LAB_2_COMPETITIONNODETAILS_H

#include "../gamemode.h"

class CompetitionNoDetailsMode : public GameModeBase {
private:
    Simulator *simulator;
    int n;
public:
    CompetitionNoDetailsMode(StrategyFactory *factory, std::vector<std::string> &strategiesNames,
                             int turnNumber, GameMatrix &matrix) : n(turnNumber) {
        simulator = new Simulator(*factory, strategiesNames, matrix);
    }

    ~CompetitionNoDetailsMode() override { delete simulator; }

    void Play() override;

    Pairs GetTotalScore() override;

    void PrintTotalScore() override;
};

#endif //LAB_2_COMPETITIONNODETAILS_H
