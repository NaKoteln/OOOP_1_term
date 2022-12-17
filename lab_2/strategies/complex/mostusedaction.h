#ifndef LAB_2_MOSTUSEDACTION_H
#define LAB_2_MOSTUSEDACTION_H

#include "../../strategy.h"

class MostUsedActionStrategy : public StrategyBase {
private:
    ActionType nextAction;

public:
    MostUsedActionStrategy(std::string strategyName) : StrategyBase(strategyName) { nextAction = COOPERATE; }

    ~MostUsedActionStrategy() override = default;

    ActionType GetAction() override;

    void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) override;
};

#endif //LAB_2_MOSTUSEDACTION_H
