#ifndef LAB_2_ALWAYSCOOPERATE_H
#define LAB_2_ALWAYSCOOPERATE_H

#include "../../strategy.h"

class AlwaysCooperateStrategy : public StrategyBase {
public:
    AlwaysCooperateStrategy(std::string strategyName) : StrategyBase(strategyName) {};
    ~AlwaysCooperateStrategy() override = default;

    ActionType GetAction() override;

    void UploadOtherAnswers(std::vector<ActionType> &answers, size_t ownNumber) override;
};

#endif //LAB_2_ALWAYSCOOPERATE_H
