#ifndef LAB_2_MOSTUSEDACTIONWITHFORGIVENESS_H
#define LAB_2_MOSTUSEDACTIONWITHFORGIVENESS_H

#include <ctime>
#include "../../strategy.h"

class MostUsedActionWithForgivenessStrategy : public StrategyBase {
private:
    ActionType nextAction;

public:
    MostUsedActionWithForgivenessStrategy(std::string strategyName) : StrategyBase(strategyName) {
        nextAction = COOPERATE;
        std::srand(std::clock());
    }

    ~MostUsedActionWithForgivenessStrategy() override = default;

    ActionType GetAction() override;

    void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) override;
};

#endif //LAB_2_MOSTUSEDACTIONWITHFORGIVENESS_H
