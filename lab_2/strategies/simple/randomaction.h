#ifndef LAB_2_RANDOMACTION_H
#define LAB_2_RANDOMACTION_H

#include <ctime>
#include "../../strategy.h"

class RandomActionStrategy : public StrategyBase {
public:
    RandomActionStrategy(std::string strategyName) : StrategyBase(strategyName) { std::srand(std::clock()); };

    ~RandomActionStrategy() override = default;

    ActionType GetAction();

    void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber);

};


#endif //LAB_2_RANDOMACTION_H
