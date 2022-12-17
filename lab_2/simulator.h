#ifndef LAB_2_SIMULATOR_H
#define LAB_2_SIMULATOR_H

#include "factory.h"

class Simulator {
private:
    using Pairs = std::vector<std::pair<std::string, int>>;
    std::vector<StrategyBase *> strategies;
    GameMatrix gameMatrix;
public:
    Simulator(StrategyFactory &factory, std::vector<std::string> &strategiesNames, GameMatrix &matrix);

    ~Simulator();

    std::vector<ActionType> DoNextTurn();

    std::vector<int> GetScoresFromAnswers(std::vector<ActionType> &answers);

    void AddScores(std::vector<int> &scores);

    void UploadOtherAnswers(std::vector<ActionType> &answers);

    Pairs GetTotalScores();
};

#endif //LAB_2_SIMULATOR_H
